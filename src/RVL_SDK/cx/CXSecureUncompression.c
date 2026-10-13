#include <kdc/revolution/CX.h>

//https://decomp.me/scratch/n2Kai
s32 CXSecureUncompressLZ(const void* src, u32 length, void* dst) {
    const u8* pSrc = src;
    u8* pDst = dst;

    u32 size = CXiConvertEndian32_(IN_BUFFER_AT(u32, pSrc, 0)) >> 8;
    s32 remainingLength = length;

    u8 secstat = CXiConvertEndian32_(IN_BUFFER_AT(u32, pSrc, 0)) & 0xFF;
    BOOL stat;

    if (IN_BUFFER_AT(u8, pSrc, 0) & 0x0F) {
        stat = TRUE;
    } else {
        stat = FALSE;
    }

    if ((secstat & CX_COMPRESSION_TYPE_MASK) != CX_COMPRESSION_TYPE_LZ) {
        return CX_SECURE_ERR_BAD_FILE_TYPE;
    }

    if ((secstat & 0x0F) != 0 && (secstat & 0x0F) != 1) {
        return CX_SECURE_ERR_BAD_FILE_TYPE;
    }

    if (length <= 4) {
        return CX_SECURE_ERR_BUFFER_TOO_SMALL;
    }

    pSrc += sizeof(u32);
    remainingLength -= sizeof(u32);

    if (!size) {
        if (remainingLength < 4) {
            return CX_SECURE_ERR_BUFFER_TOO_SMALL;
        }

        size = CXiConvertEndian32_(IN_BUFFER_AT(u32, pSrc, 0));
        pSrc += sizeof(u32);
        remainingLength -= sizeof(u32);
    }

    while (size) {
        u32 i;
        u32 flags = *pSrc++;
        remainingLength--;
        if (remainingLength < 0) {
            return CX_SECURE_ERR_BUFFER_TOO_SMALL;
        }
        for (i = 0; i < 8; i++) {
            if (!(flags & 0x80)) {
                *pDst++ = *pSrc++;

                remainingLength--;
                if (remainingLength < 0) {
                    return CX_SECURE_ERR_BUFFER_TOO_SMALL;
                }

                size--;
            } else {
                s32 length2 = *pSrc >> 4;
                s32 offset;

                if (!stat) {
                    length2 += 3;
                } else {
                    if (length2 == 0x01) {
                        length2 = (*pSrc++ & 0x0F) << 12;
                        length2 |= *pSrc++ << 4;
                        length2 |= *pSrc >> 4;
                        length2 += 0x111;

                        remainingLength -= 2;
                    } else if (length2 == 0x00) {
                        length2 = (*pSrc++ & 0x0F) << 4;
                        length2 |= *pSrc >> 4;
                        length2 += 0x11;

                        remainingLength -= 1;
                    } else {
                        length2 += 0x01;
                    }
                }

                offset = (*pSrc++ & 0x0F) << 8;
                offset = (offset | *pSrc++) + 1;

                remainingLength -= 2;
                if (remainingLength < 0) {
                    return CX_SECURE_ERR_BUFFER_TOO_SMALL;
                }

                if (length2 > size) {
                    return CX_SECURE_ERR_BAD_FILE_SIZE;
                }

                if ((u32)&pDst[-offset] < (u32)dst) {
                    return CX_SECURE_ERR_BAD_FILE_SIZE;
                }

                size -= length2;

                do {
#if defined(__MWERKS__)
                    // ERRATUM: Unsequenced modification and access to pDst
                    /* Here, the compiler has decided to evaluate the left hand
                     * side pDst first, then the right hand side pDst, then the
                     * side effect of the post-increment on the left hand side
                     * pDst.
                     */
                    *pDst++ = pDst[-offset];
#else
                    // equivalent defined version
                    *pDst = pDst[-offset];
                    pDst++;
#endif
                } while (--length2 > 0);
            }

            if (!size) {
                break;
            }

            flags <<= 1;
        }
    }

    if (remainingLength > 32) {
        return CX_SECURE_ERR_BUFFER_TOO_LARGE;
    }

    return CX_SECURE_ERR_OK;
}
