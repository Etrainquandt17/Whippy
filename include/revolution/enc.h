#ifndef REVOLUTION_ENC_H
#define REVOLUTION_ENC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

int ENCConvertStringUtf8ToUtf16(u16* dst, s32* dstSize, const u8* src, s32* srcSize);

#ifdef __cplusplus
}
#endif

#endif
