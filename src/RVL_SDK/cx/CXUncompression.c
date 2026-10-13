#include <kdc/revolution/CX.h>

//from https://github.com/koopthekoopa/wii-ipl/blob/5947da829f79e49a8c4c58f3ad168f156740b808/libs/RVL_SDK/src/cx/CXUncompression.c
u32 CXGetUncompressedSize(const void* src) {
    u32 size = CXiConvertEndian32_(IN_BUFFER_AT(u32, src, 0)) >> 8;
    if (!size) {
        size = CXiConvertEndian32_(IN_BUFFER_AT(u32, src, 4));
    }

    return size;
}
