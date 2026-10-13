#include "util/CharacterEncodeUtil.h"

#include "revolution/enc.h"
#include "std/cstring.h"
#include "std/min.h"

namespace util {
namespace CharacterEncodeUtil {

void UTF8ToUTF16(wchar_t* dst, u32 dstLength, const char* src) {
    UTF8ToUTF16(dst, dstLength, src, strlen(src));
}

bool UTF8ToUTF16(wchar_t* dst, u32 dstLength, const char* src, u32 srcLength) {
    s32 srcSize = srcLength;
    s32 dstSize = dstLength;
    if (ENCConvertStringUtf8ToUtf16(reinterpret_cast<u16*>(dst), &dstSize, reinterpret_cast<const u8*>(src), &srcSize) != 0) {
        return false;
    }
    dst[std::min<s32>(dstSize, dstLength - 1)] = 0;
    return true;
}

}}  // namespace util::CharacterEncodeUtil
