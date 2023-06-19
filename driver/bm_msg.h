#ifndef BM_MSG_H
#define BM_MSG_H

typedef enum {
	BM_API_ID_RESERVED                         = 0,
	BM_API_ID_MEM_SET                          = 1,
	BM_API_ID_MEM_CPY                          = 2,
	/*
	 * Basic Computation APIs
	 */
	BM_API_ID_MD_SCALAR                        = 3,
	BM_API_ID_MD_SUM                           = 4,
	BM_API_ID_MD_LINEAR                        = 5,
	BM_API_ID_MD_CMP                           = 6,
	BM_API_ID_MD_SFU                           = 7,
	BM_API_ID_IMG_SUM                          = 8,
	BM_API_ID_FLOAT2INT8                       = 9,
	/*
	 * Layer APIs
	 */
	BM_API_ID_DROPOUT_FWD                      = 10,
	BM_API_ID_DROPOUT_BWD                      = 11,
	BM_API_ID_ACCURACY_LAYER                   = 12,
	BM_API_ID_LOG_FWD                          = 13,
	BM_API_ID_LOG_BWD                          = 14,
	BM_API_ID_SIGMOID_CROSS_ENTROPY_LOSS_FWD   = 15,
	BM_API_ID_SIGMOID_CROSS_ENTROPY_LOSS_BWD   = 16,
	BM_API_ID_CONTRASTIVE_LOSS_FWD             = 17,
	BM_API_ID_CONTRASTIVE_LOSS_BWD             = 18,
	BM_API_ID_FILTER_FWD                       = 19,
	BM_API_ID_FILTER_BWD                       = 20,
	BM_API_ID_SPLIT_BWD                        = 21,
	BM_API_ID_PRELU_FWD                        = 22,
	BM_API_ID_PRELU_BWD                        = 23,
	BM_API_ID_SCALE_FWD                        = 24,
	BM_API_ID_SCALE_BWD                        = 25,
	BM_API_ID_THRESHOLD_FWD                    = 26,
	BM_API_ID_EXP_FWD                          = 27,
	BM_API_ID_EXP_BWD                          = 28,
	BM_API_ID_POWER_FWD                        = 29,
	BM_API_ID_POWER_BWD                        = 30,
	BM_API_ID_EUCLIDEAN_LOSS_FWD               = 31,
	BM_API_ID_EUCLIDEAN_LOSS_BWD               = 32,
	BM_API_ID_SILENCE_BWD                      = 33,
	BM_API_ID_LSTM_UNIT_FWD                    = 34,
	BM_API_ID_LSTM_UNIT_BWD                    = 35,
	BM_API_ID_ELTWISE_FWD                      = 36,
	BM_API_ID_ELTWISE_BWD                      = 37,
	BM_API_ID_BIAS_FWD                         = 38,
	BM_API_ID_BIAS_BWD                         = 39,
	BM_API_ID_ELU_FWD                          = 40,
	BM_API_ID_ELU_BWD                          = 41,
	BM_API_ID_ABSVAL_FWD                       = 42,
	BM_API_ID_ABSVAL_BWD                       = 43,
	BM_API_ID_BNLL_FWD                         = 44,
	BM_API_ID_BNLL_BWD                         = 45,
	BM_API_ID_PERMUTE                          = 46,
	BM_API_ID_ROI_POOLING_FWD                  = 47,
	BM_API_ID_NORMALIZE_FWD                    = 48,
	BM_API_ID_CONV_FWD_PARALLEL                = 49,
	BM_API_ID_DECONV_FWD_PARALLEL              = 50,
	BM_API_ID_CONV_BWD_BIAS_PARALLEL           = 51,
	BM_API_ID_POOLING_FWD_PARALLEL             = 52,
	BM_API_ID_POOLING_BWD_PARALLEL             = 53,
//  BM_API_ID_FC_FWD_PARALLEL                  = 54,
	BM_API_ID_FC_BWD_PARALLEL                  = 55,
	BM_API_ID_LRN_FWD_PARALLEL                 = 56,
	BM_API_ID_LRN_BWD_PARALLEL                 = 57,
	BM_API_ID_BN_FWD_INF_PARALLEL              = 58,
	BM_API_ID_BN_FWD_TRAIN_PARALLEL            = 59,
	BM_API_ID_BN_BWD_PARALLEL                  = 60,
//  BM_API_ID_SIGMOID_FWD_PARALLEL             = 61,
	BM_API_ID_SIGMOID_BWD_PARALLEL             = 62,
//  BM_API_ID_TANH_FWD_PARALLEL                = 63,
	BM_API_ID_TANH_BWD_PARALLEL                = 64,
	BM_API_ID_RELU_FWD_PARALLEL                = 65,
	BM_API_ID_RELU_BWD_PARALLEL                = 66,
	BM_API_ID_SOFTMAX_FWD_PARALLEL             = 67,
	BM_API_ID_SOFTMAX_BWD_PARALLEL             = 68,
	BM_API_ID_SOFTMAX_LOSS_FWD_PARALLEL        = 69,
	BM_API_ID_SOFTMAX_LOSS_BWD_PARALLEL        = 70,
	BM_API_ID_SOFTMAX_LOSS_BIDIR_PARALLEL      = 71,
	BM_API_ID_COEFF_UPDATE_SGD_PARALLEL        = 72,
	BM_API_ID_UPSAMPLE_FWD_PARALLEL            = 73,
	BM_API_ID_UPSAMPLE_BWD_PARALLEL            = 74,
	BM_API_ID_MULTIREGION_FWD_PARALLEL         = 75,
	BM_API_ID_MULTIREGION_BWD_PARALLEL         = 76,
	BM_API_ID_CONV_CORRELATION_PARALLEL        = 77,
	BM_API_ID_WINOGRAD_BWD_BOTTOM_DIFF_PARALLEL = 78,
	BM_API_ID_REGULARIZATION_L1_PARALLEL        = 79,
	BM_API_ID_LSTM_FWD                          = 82,
	BM_API_ID_CONV_FWD_FIX8B_PARALLEL           = 83,
	BM_API_ID_ELTWISE_FWD_FIX8B_PARALLEL        = 84,
	BM_API_ID_FC_FWD_FIX8B_PARALLEL             = 85,
	BM_API_ID_BN_FWD_FIX8B_PARALLEL             = 86,
	BM_API_ID_SCALE_FWD_FIX8B_PARALLEL          = 87,
	BM_API_ID_POOLING_FWD_FIX8B_PARALLEL        = 88,
	BM_API_ID_FLOAT_TO_INT_PARALLEL             = 89,
	BM_API_ID_INT_TO_FLOAT_PARALLEL             = 90,
	BM_API_ID_CONCAT                            = 91,
	BM_API_ID_CONCAT_FIX8B                      = 92,
	BM_API_ID_GLOBAL_MEMCPY                     = 93,
	BM_API_ID_CROP                              = 94,
	BM_API_ID_POOLING_FWD_TRAIN_PARALLEL        = 95,
	BM_API_ID_BNSCALE_FWD_FIX8B_PARALLEL       =  96,
	BM_API_ID_DEPTHWISE_FIX8B_FWD_PARALLEL      = 97,
	// BM BLAS API
	BM_API_ID_SCALE                            = 98,
	BM_API_ID_AXPY                             = 99,
	BM_API_ID_DOT                              = 100,
	BM_API_ID_ASUM                             = 101,
	BM_API_ID_NRM2                             = 102,
	BM_API_ID_ROT                              = 103,
	BM_API_ID_ROTM                             = 104,
	BM_API_ID_GEMM                             = 105,
	BM_API_ID_SYMM                             = 106,
	BM_API_ID_TRMM                             = 107,
	BM_API_ID_TPMV                             = 108,
	BM_API_ID_TBMV                             = 109,

	// FULLNET API
	// DO NOT change BM_API_ID_MULTI_FULLNET and BM_API_ID_DYNAMIC_FULLNET values,
	// which are used in nntoolchain "bmdnn_func.h"
	BM_API_ID_MULTI_FULLNET                    = 110,
	BM_API_ID_DYNAMIC_FULLNET                  = 111,

	// BMCV API
	BM_API_ID_CV_WARP                          = 112,
	BM_API_ID_CV_RESIZE                        = 113,
	BM_API_ID_CV_YUV2RGB                       = 114,

	BM_API_ID_SLICE_FWD                        = 115,
	BM_API_ID_TILE_FWD                         = 116,
	BM_API_ID_TRANSPOSE                        = 117,
	BM_API_ID_TRANSPOSE_FIX8B                  = 118,
	BM_API_ID_TILE_FIX8B_FWD                   = 119,
	BM_API_ID_BATCH2SPACE_FIX8B                = 120,
	BM_API_ID_SPACE2BATCH_FIX8B                = 121,

	BM_API_ID_POOLING_FWD_TRAIN_INDEX_PARALLEL  = 122,
	BM_API_ID_1D_SCALAR                         = 123,
	BM_API_ID_1D_SFU                            = 124,
	BM_API_ID_CV_GEN_PROPOSAL                   = 126,
	BM_API_ID_WORD2VEC                          = 127,
	BM_API_ID_SUM_X2N                           = 128,
	BM_API_ID_MD_OPS                            = 129,

	// New API
	BM_API_ID_DECONV_FIX8B_FWD_PARALLEL         = 130,
	BM_API_ID_CV_NMS                            = 131,
	BM_API_ID_MEMCPY_BYTE                       = 136,
	BM_API_ID_MEMCPY_WSTRIDE                    = 137,
	BM_API_ID_F32_IS                           = 139,
	BM_API_ID_CTCLOSS                          = 140,
	BM_API_ID_NORMALIZE_FIX8B_FWD              = 141,
	BM_API_ID_PERMUTE_FIX8B_FWD                = 142,
	BM_API_ID_SLICE_FIX8B_FWD                  = 143,
	BM_API_ID_PAD                              = 144,
	BM_API_ID_PAD_FIX8B                        = 145,
	BM_API_ID_SPLIT_TF_FIX8B                   = 146,

	BM_API_ID_UNARY                            = 147,
	BM_API_ID_BINARY                           = 148,
	BM_API_ID_SIMPLE_BINARY                    = 149,
	BM_API_ID_SELECT                           = 150,
	BM_API_ID_SIMPLE_SELECT                    = 151,
	BM_API_ID_DEPTHWISE_FWD                    = 152,
	BM_API_ID_DEPTHWISE_BWD_INPUT              = 153,
	BM_API_ID_DEPTHWISE_BWD_FILTER             = 154,
	BM_API_ID_PSROIPOOLING_FWD                 = 155,
	// DO NOT change BM_API_ID_DYNAMIC_FULLNET_EX value which is used in nntoolchain "bmdnn_func.h"
	BM_API_ID_DYNAMIC_FULLNET_EX               = 156,
	BM_API_ID_ARG                              = 157,
	BM_API_ID_ARG_FIX8B                        = 158,
	BM_API_ID_SHUFFLE_CHANNEL_FWD              = 159,
	BM_API_ID_SHUFFLE_CHANNEL_FIX8B_FWD        = 160,
	BM_API_ID_STRIDE_SLICE                     = 161,
	BM_API_ID_FC_WEIGHT_DECOMPRESS             = 162,
	BM_API_ID_INTERP_FWD_PARALLEL              = 163,
	BM_API_ID_BIAS_FIX8B_FWD                   = 164,
	BM_API_ID_STRIDE_SLICE_FIX8B               = 165,
	BM_API_ID_ADAPTIVE_POOLING_FWD             = 166,
	BM_API_ID_ADAPTIVE_POOLING_FIX8B_FWD       = 167,
	BM_API_ID_REDUCE_FIX8B                     = 168,
	BM_API_ID_ELTWISE_BINARY_FWD_FIX8B_PARALLEL = 169,
	BM_API_ID_CONST_BINARY_FWD_FIX8B_PARALLEL   = 170,
	BM_API_ID_BROADCAST_BINARY_FWD_FIX8B_PARALLEL = 171,

	BM_API_ID_SIGMOID_FWD_PARALLEL_FIX8B       = 172,
	BM_API_ID_TANH_FWD_PARALLEL_FIX8B          = 173,
	BM_API_ID_ACTIVE_FWD                       = 174,
	BM_API_ID_ACTIVE_FWD_FIX8B                 = 175,
	BM_API_ID_SSD_DETECT_OUT                   = 176,
	BM_API_ID_MEMSET_BYTE                      = 177,
	BM_API_ID_YOLOV3_DETECT_OUT                = 178,

	BM_API_ID_REDUCE                           = 200,
	BM_API_ID_SEGMENT_REDUCE                   = 201,
	BM_API_ID_LRN_FIX8B_FWD_PARALLEL           = 202,
	// BM_CV
	BM_API_ID_CV_CONVERT_TO                    = 500,
	BM_API_ID_CV_GEN_PROP_AND_NMS              = 501,
	BM_API_ID_CV_CONVERT_TO_INTERGRATED        = 502,
	BM_API_ID_CV_SROT_TEST                     = 503,
	BM_API_ID_CV_FEATURE_MATCH                 = 504,
	BM_API_ID_CV_STORAGE_CONVERT               = 505,
	BM_API_ID_CV_CORRECT_LAYOUT                   = 506,
	BM_API_ID_CV_COPY_TO                       = 507,
	BM_API_ID_CV_SORT                          = 508,
	BM_API_ID_CV_FEATURE_MATCH_FIX8B           = 509,
	BM_API_ID_CV_WARP_BILINEAR   = 510,

	// Management API
	BM_API_ID_FLASH_UPDATE                     = 600,

	// Bmnetp API
	BM_API_ID_TOPK                             = 700,
	BM_API_ID_CUMSUM                           = 701,
	BM_API_ID_WHERE                            = 702,
	BM_API_ID_MASKED_SELECT                    = 703,

	// bmnetd API
	BM_API_ID_YOLO                             = 800,

	// for same with bm168x
	BM_API_ID_FC_FWD_PARALLEL                  = 900,
	BM_API_ID_SIGMOID_FWD_PARALLEL             = 901,
	BM_API_ID_TANH_FWD_PARALLEL                = 902,

	BM_API_ID_CONV_FWD_FIX16B_PARALLEL         = 983,
	BM_API_ID_DEPTHWISE_FIX16B_FWD_PARALLEL    = 984,
	BM_API_ID_PERCHANNEL_SHIFT                 = 985,

	BM_API_ID_MAX,

	BM_API_ID_START_CPU = 0x80000001,
	BM_API_ID_OPEN_PROCESS = 0x80000002,
	BM_API_ID_LOAD_LIBRARY = 0x80000003,
	BM_API_ID_EXEC_FUNCTION = 0x80000004,
	BM_API_ID_MAP_PHY_ADDR = 0x80000005,
	BM_API_ID_CLOSE_PROCESS = 0x80000006,
	BM_API_ID_SET_LOG = 0x80000007,
	BM_API_ID_GET_LOG = 0x80000008,
	BM_API_ID_SET_TIME = 0x80000009,
	BM_API_ID_UNLOAD_LIBRARY = 0x8000000b,
	BM_API_ID_CPU_MAX,
	BM_API_QUIT = 0xffffffff,
} bm_api_id_t;

#endif
