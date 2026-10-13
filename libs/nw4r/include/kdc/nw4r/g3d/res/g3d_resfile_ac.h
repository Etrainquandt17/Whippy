#ifndef NW4R_G3D_RESCOMMON_AC_H
#define NW4R_G3D_RESCOMMON_AC_H
#include "kdc/common.h"

#include "kdc/revolution/GX.h" // IWYU pragma: export
#include "kdc/nw4r/NW4RAssert.hpp"

/******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/

/**
 * ResFile Asserts
 */

 #define NW4R_G3D_RES_COMPAREVAL_ASSERT(filename, linenumber, comparevalule, resfile) \
    void* p = resfile->ptr(); \
    NW4RAssert_FileLine(filename, linenumber, !((u32)p & comparevalule));  \

#define NW4R_G3D_COMMON_AC_ASSERT_PTR(pointer) \
    (void)0;(void)0;(void)0;  /* TODO: Remove this */ \
    NW4RAssertPointerNonnull_FileLine("g3d_rescommon_ac.h", 140, pointer); \

#endif
