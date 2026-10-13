#ifndef UTIL_CHARACTERENCODEUTIL_H
#define UTIL_CHARACTERENCODEUTIL_H

#include "types.h"

namespace util {

namespace CharacterEncodeUtil {

void UTF8ToUTF16(wchar_t* dst, u32 dstLength, const char* src);
bool UTF8ToUTF16(wchar_t* dst, u32 dstLength, const char* src, u32 srcLength);

}

}

#endif
