#include <iostream>
#include "bmcv_api_ext.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "md5.h"
#include <assert.h>
#include <vector>
#ifdef __linux__
#include <sys/time.h>
#else
#include <windows.h>
#include "time.h"
#include "md5.h"
#endif
#include "test_misc.h"

using namespace std;

typedef enum {
    AND = 1,
    OR = 2,
    XOR = 3
} operation;

static void fill(
        unsigned char* input,
        int width,
        int height,
        int flag) {
    switch(flag){
        case 1:
            {
                int count = 10;
                for(int i = 0; i< width * height * 3; i++ ){
                    input[i] = count;
                    count++;
                    if(count == 101)
                        count = 10;
                }
                break;
            }
        case 2:
            {
                int count = 1;
                for(int i = 0; i< width * height * 3; i++){
                    input[i] = count;
                    count++;
                    if(count == 9)
                        count = 1;
                }
                break;
            }
        default:
           break;
    }
}

static int bitwise_tpu(
        unsigned char* input1,
        unsigned char* input2,
        unsigned char* output,
        int height,
        int width,
        int format,
        int op) {
    bm_handle_t handle;
    bm_status_t ret = bm_dev_request(&handle, 0);
    if (ret != BM_SUCCESS) {
        printf("Create bm handle failed. ret = %d\n", ret);
        return -1;
    }
    bm_image input1_img;
    bm_image input2_img;
    bm_image output_img;
    bm_image_create(handle, height, width, (bm_image_format_ext)format, DATA_TYPE_EXT_1N_BYTE, &input1_img);
    bm_image_create(handle, height, width, (bm_image_format_ext)format, DATA_TYPE_EXT_1N_BYTE, &input2_img);
    bm_image_create(handle, height, width, (bm_image_format_ext)format, DATA_TYPE_EXT_1N_BYTE, &output_img);
    bm_image_alloc_dev_mem(input1_img);
    bm_image_alloc_dev_mem(input2_img);
    bm_image_alloc_dev_mem(output_img);
    unsigned char* in1_ptr[3] = {input1, input1 + height * width, input1 + 2 * height * width};
    bm_image_copy_host_to_device(input1_img, (void **)in1_ptr);
    unsigned char* in2_ptr[3] = {input2, input2 + height * width, input2 + 2 * height * width};
    bm_image_copy_host_to_device(input2_img, (void **)in2_ptr);

    struct timeval t1, t2;
    gettimeofday_(&t1);
    switch (op)
    {
    case AND:
        bmcv_image_bitwise_and(handle, input1_img, input2_img, output_img);
        break;
    case OR:
        bmcv_image_bitwise_or(handle, input1_img, input2_img, output_img);
        break;
    case XOR:
        bmcv_image_bitwise_xor(handle, input1_img, input2_img, output_img);
        break;
    }
    gettimeofday_(&t2);
    cout << "bitwise TPU using time: " << ((t2.tv_sec - t1.tv_sec) * 1000000 + t2.tv_usec - t1.tv_usec) << "us" << endl;

    unsigned char* out_ptr[3] = {output, output + height * width, output + 2 * height * width};
    bm_image_copy_device_to_host(output_img, (void **)out_ptr);
    bm_image_destroy(input1_img);
    bm_image_destroy(input2_img);
    bm_image_destroy(output_img);
    bm_dev_free(handle);
    return 0;
}

static vector<int> get_image_size(int format, int width, int height) {
    vector<int> size;
    switch (format) {
        case FORMAT_YUV420P:
            size.push_back(width * height);
            size.push_back(width * height / 4);
            size.push_back(width * height / 4);
            break;
        case FORMAT_YUV422P:
            size.push_back(width * height);
            size.push_back(width * height / 2);
            size.push_back(width * height / 2);
            break;
        case FORMAT_YUV444P:
        case FORMAT_RGB_PLANAR:
        case FORMAT_BGR_PLANAR:
        case FORMAT_RGB_PACKED:
        case FORMAT_BGR_PACKED:
        case FORMAT_RGBP_SEPARATE:
        case FORMAT_BGRP_SEPARATE:
            size.push_back(width * height);
            size.push_back(width * height);
            size.push_back(width * height);
            break;
        case FORMAT_NV12:
        case FORMAT_NV21:
            size.push_back(width * height);
            size.push_back(width * height / 2);
            break;
        case FORMAT_NV16:
        case FORMAT_NV61:
        case FORMAT_NV24:
            size.push_back(width * height);
            size.push_back(width * height);
            break;
        case FORMAT_GRAY:
            size.push_back(width * height);
            break;
        default:
            cout << "format error" << endl;
    }
    return size;
}

static int cmp(
        unsigned char* got,
        unsigned char* exp,
        int format,
        int width,
        int height) {
    vector<int> len = get_image_size(format, width, height);
    for (unsigned int i = 0; i < len.size(); i++) {
        int done = 0;
        for (int j = 0; j < len[i]; j++) {
            if (abs(got[done + j] - exp[done + j]) > 1) {
                printf("cmp error: plane=%d  idx=%d  exp=%d  got=%d\n", i, j, exp[done + j], got[done + j]);
                return -1;
            }
        }
        done += len[i];
    }
    return 0;
}

static string  unsignedCharToHex(unsigned char ch[16]){
    const char hex_chars[] = "0123456789abcdef";
    string result = "";
    for(int i = 0; i < 16; i++){
        unsigned int highHalfByte = (ch[i] >> 4) & 0x0f;
        unsigned int lowHalfByte = (ch[i] & 0x0f);
        result += hex_chars[highHalfByte];
        result += hex_chars[lowHalfByte];
    }
    return result;
}

static int cmpv2(unsigned char* got, unsigned char* exp ,int width, int height, int channel){
    unsigned char* md5_tpuOut = new unsigned char[16];
    md5_get(got, (sizeof(unsigned char) * channel * height * width), md5_tpuOut);
    if(0 != strcmp((unsignedCharToHex(md5_tpuOut).c_str()), (const char*)exp)){
        cout << "cmp error!" << endl;
        delete [] md5_tpuOut;
        return -1;
    }
    delete [] md5_tpuOut;
    return 0;
}

static int test_bitwise_random(
        int height,
        int width,
        int format) {
    struct timespec tp;
    clock_gettime_(0, &tp);

    unsigned int seed = tp.tv_nsec;
    srand(seed);
    cout << "seed = " << seed << endl;
    cout << "format: " << format << endl;
    cout << "width: " << width << "  height: " << height << endl;
    unsigned char* input1_data = new unsigned char [width * height * 3];
    unsigned char* input2_data = new unsigned char [width * height * 3];
    unsigned char* output_tpu = new unsigned char [width * height * 3];
    fill(input1_data, width, height, 1);
    fill(input2_data, width, height, 2);
    fill(output_tpu, width, height, 2);
    unsigned char ocv_and_md5[] = "e0b318d9658fd72dba39643f59d74185";
    bitwise_tpu(
        input1_data,
        input2_data,
        output_tpu,
        height, width,
        format,
        AND);
    int ret = cmpv2(output_tpu, ocv_and_md5, width ,height, 3);
    if( ret != 0)
        return -1;
    unsigned char ocv_or_md5[] = "1af8b9b086679fe653387fcb7934a792";
    bitwise_tpu(
        input1_data,
        input2_data,
        output_tpu,
        height, width,
        format,
        OR);
    ret = cmpv2(output_tpu, ocv_or_md5, width ,height, 3);
    if( ret != 0)
        return -1;
    unsigned char ocv_xor_md5[] = "be18e61b95fdbc40a71fc548ebf00621";
    bitwise_tpu(
        input1_data,
        input2_data,
        output_tpu,
        height, width,
        format,
        XOR);
    ret = cmpv2(output_tpu, ocv_xor_md5, width ,height, 3);
    if( ret != 0)
        return -1;
    delete [] input1_data;
    delete [] input2_data;
    delete [] output_tpu;
    return ret;
}

int main(int argc, char* args[]) {
    int loop = 1;
    int height = 1080;
    int width = 1920;
    int format = FORMAT_RGBP_SEPARATE;
    if (argc > 1) loop = atoi(args[1]);
    int ret = 0;
    for (int i = 0; i < loop; i++) {
        ret = test_bitwise_random(height, width, format);
        if (ret) {
            cout << "test bitwise failed" << endl;
            return ret;
        }
    }
    cout << "Compare TPU result with OpenCV successfully!" << endl;
    return 0;
}
