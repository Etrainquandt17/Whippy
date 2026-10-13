#ifndef REVOLUTION_OS_OSCACHE_H
#define REVOLUTION_OS_OSCACHE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void DCInvalidateRange(void* addr, u32 size);
void DCStoreRangeNoSync(void* addr, u32 size);

#ifdef __cplusplus
}
#endif

#endif
