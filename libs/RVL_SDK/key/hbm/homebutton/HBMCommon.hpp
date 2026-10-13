#ifndef RVL_SDK_HBM_HOMEBUTTON_COMMON_HPP
#define RVL_SDK_HBM_HOMEBUTTON_COMMON_HPP

#include <key/revolution/HBM/HBMCommon.h> // IWYU pragma: export

/*******************************************************************************
 * headers
 */

#include <key/types.h> // u32

#if 0
#include <key/revolution/MEM/mem_allocator.h>
#endif

#include <key/hbm/context_rvl.h>

/*******************************************************************************
 * external variables
 */

// .sdata
extern "C" MEMAllocator *spAllocator;

/*******************************************************************************
 * classes and functions
 */

// library internals
void *HBMAllocMem(u32 length);
void HBMFreeMem(void *ptr);

#endif // RVL_SDK_HBM_HOMEBUTTON_COMMON_HPP
