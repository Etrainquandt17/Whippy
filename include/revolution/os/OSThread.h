#ifndef REVOLUTION_OS_OSTHREAD_H
#define REVOLUTION_OS_OSTHREAD_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: members. 0x318 bytes, aligned to 8 for the floating-point registers of its context.
typedef struct OSThread {
    union {
        u32 words[0x318 / 4];
        f64 align;
    };
} OSThread;

typedef void* (*OSThreadFunc)(void* arg);

OSThread* OSGetCurrentThread(void);
int OSCreateThread(OSThread* thread, OSThreadFunc func, void* arg, void* stack, u32 stackSize, s32 priority, u16 attr);
void OSCancelThread(OSThread* thread);
s32 OSResumeThread(OSThread* thread);
s32 OSGetThreadPriority(OSThread* thread);

#ifdef __cplusplus
}
#endif

#endif
