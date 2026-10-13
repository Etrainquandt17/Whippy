#ifndef RVL_CX_H
#define RVL_CX_H

#include <kdc/types.h>

// .text: [0x803cee90, 0x803d0b20]

#ifdef __cplusplus
extern "C" {
#endif

enum CXSecureResult {
    CX_SECURE_ERR_BAD_FILE_TABLE  = -5,
    CX_SECURE_ERR_BAD_FILE_SIZE  = -4,
    CX_SECURE_ERR_BUFFER_TOO_LARGE = -3,
    CX_SECURE_ERR_BUFFER_TOO_SMALL = -2,
    CX_SECURE_ERR_BAD_FILE_TYPE = -1,
    CX_SECURE_ERR_OK = 0,
};

//from https://github.com/koopthekoopa/wii-ipl/blob/main/libs/RVL_SDK/include/private/cx.h
#define CX_COMPRESSION_TYPE_MASK 0xF0
#define CX_COMPRESSION_TYPE_LZ 0x10
#define IN_BUFFER_AT(type_, buf_, offset_) (*((__typeof__(type_)*)((u32)(buf_) + (u32)(offset_))))

#define CXiConvertEndian32_ CXiConvertEndian_

static inline u32 CXiConvertEndian_(u32 x) {
    return ((x & 0xFF000000) >> 24) | ((x & 0x00FF0000) >> 8) | ((x & 0x0000FF00) << 8) | ((x & 0x000000FF) << 24);
}

static inline u16 CXiConvertEndian16_(u16 x) {
    return ((x & 0xFF00) >> 8) | ((x & 0x00FF) << 8);
}

//literally only two used lololol
u32 CXGetUncompressedSize(const void *);
s32 CXSecureUncompressLZ(const void* src, u32 length, void* dst);

#ifdef __cplusplus
}
#endif

#endif
