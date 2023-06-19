#include "boot_test.h"
#include "cache.h"
#include "dec_test.h"
#include "testcase_wave.h"
#include "module_testcase.h"

extern void invalidate_dcache_all(void);
extern int TestEncoder();

int test_cnm(int coreIdx, decoder_param_t *decoderParam)
{
    TestDecConfig param;
    char *p;

    /* init para */
    param.instIdx = 0;

    param.bitstreamMode = 0;        //BS_MODE_INTERRUPT
    param.bitFormat = decoderParam->boda_codec_type;            //STD_AVC H264 standard
    param.coreIdx = coreIdx;             // core 0 for boda960
    param.enableWTL = decoderParam->boda_wtl_en;
    param.frameEndian = 0;
    param.streamEndian = 0;         // VDI_LITTLE_ENDIAN
    param.mapType = decoderParam->boda_map_typ;    //TILED_FRAME_V_MAP; //LINEAR_FRAME_MAP;      // TILED_FRAME_MB_RASTER_MAP;
    param.cbcrInterleave = 1;
    param.coda9.enableMvc = decoderParam->mvc_en;      // disable MVC
    param.coda9.enableTiled2Linear = decoderParam->t2l_en; // enable tiled to linear mapping for display
    param.coda9.tiled2LinearMode = decoderParam->t2l_mode;    // frame map
    if (param.coda9.enableTiled2Linear)
        param.coda9.enableBWB = 0;
    else
        param.coda9.enableBWB = 1;          // enable 8 burst in linear mode, disable it when enableTiled2Linear=1 for performance
    param.coda9.enableDeblock = 0;      // not available for AVC
    param.coda9.mp4class = decoderParam->mpeg4_class;            // not available for mpeg4
    param.coda9.frameCacheBypass = decoderParam->cache_bypass;   // MC/ME cache enable (To be optimized)
    param.coda9.frameCacheBurst = 0;    // burst 4 / 8 selection (to be opitmized)
    param.coda9.frameCacheMerge = 0;     // horizontal without merge (to be optimized)
    param.coda9.frameCacheWayShape = 0;  // chroma cache way/luma cache way
    param.coda9.rotate = decoderParam->rotate_en;
    param.coda9.mirror = decoderParam->mirror_en;
    param.coda9.enableDering = 0;

    param.wave.fbcMode = 0x0;           // best for bandwidth
    param.wave.bwOptimization = decoderParam->bwb_en;     // only valid for WTL enable case
    param.wave.numVCores = 1;

    param.wtlMode = decoderParam->wtl_mode;                  // frame linear map mode
    param.wtlFormat = decoderParam->wtl_format;                // FORMAT_420

    param.nv21 = 0;                     // nv12

    param.secondaryAXI = decoderParam->secaxi_en;           // enable secondary AXI for H264

    param.inputPath[0] = '\0';      // feed data into 0xF0000000 in advanced.
    param.enableUserData = 0;       // no user data reported
    param.renderType = RENDER_DEVICE_NULL;      // no display output

    param.bsSize = 0xA00000;        // 4M for ES buffer
    param.bsBlockSize = 0x20000;
    param.feedingMode = 0;          // fixed size feeding

    param.compareType = 1; // 1 - YUV compare (param.refYuvPath to be set), 0 - NO compare 2 - MD5
    param.refYuvPath[0] = '\0';
    param.md5Path[0] = '\0';
    p = "\0";         // "dump.yuv"

    if (param.compareType == 0)     // if no compare, dump file out
        memcpy(param.outputPath, (void *)p, strlen(p));    // no output
    else
        param.outputPath[0] = '\0';

    param.forceOutNum = 10; // output 50 frames
    param.enableLog = 0;
    param.scaleDownWidth = 0;
    param.scaleDownHeight = 0;

    return 1 - TestDecoder(&param);
}

int test_cnm_enc()
{
    uartlog("encoder testing....");
    return 1 - TestEncoder();
}
void inv_dcache_range(unsigned long start, unsigned long size)
{
    invalidate_dcache_range(start, size);
}

int testcase_wave(void)
{
    int ret = 0;
    int enc_flag = *((int *)0x4F0000000UL) == 1 ? 1 : 0;
    decoder_param_t decoder_param;

    uartlog("%s\n", __func__);

    invalidate_dcache_all();

    //AVC
    decoder_param = (decoder_param_t){0, 1, COMPRESSED_FRAME_MAP,
                                      0, 0, 1,
                                      3, 0, 0,
                                      0, 0, 0, 1, 0};
    if (enc_flag == 1)
        ret = test_cnm_enc();
    else
        ret = test_cnm(0, &decoder_param);
    uartlog("testcase wave %s\n", ret?"passed":"failed");

#if 0
    invalidate_dcache_all();
    decoder_param = (decoder_param_t){0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0xf, 0, 1, 0};
    ret = test_cnm(1, &decoder_param);

    uartlog("testcase coda core 1 %s\n", ret?"passed":"failed");
#endif

    return ret;
}

module_testcase("0", testcase_wave);

