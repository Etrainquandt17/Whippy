#ifndef RVL_SDK_OS_ARENA_H
#define RVL_SDK_OS_ARENA_H
#include <kdc/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void* OSGetMEM1ArenaHi(void);
void* OSGetMEM2ArenaHi(void);
// NOTE: Is merged into OSGetMEM1ArenaHi
void* OSGetArenaHi(void);

void* OSGetMEM1ArenaLo(void);
void* OSGetMEM2ArenaLo(void);
// NOTE: Is merged into OSGetMEM1ArenaLo
void* OSGetArenaLo(void);

void OSSetMEM1ArenaHi(void* hi);
void OSSetMEM2ArenaHi(void* hi);
// NOTE: Is merged into OSSetMEM1ArenaHi
void OSSetArenaHi(void* hi);

void OSSetMEM1ArenaLo(void* lo);
void OSSetMEM2ArenaLo(void* lo);
// NOTE: Is merged into OSetMEM1ArenaLo
void OSSetArenaLo(void* lo);

void* OSAllocFromMEM1ArenaLo(size_t size, u32 align);
void* OSAllocFromMEM2ArenaLo(size_t size, u32 align);
#ifdef __cplusplus
}
#endif
#endif
