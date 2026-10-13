#ifndef REVOLUTION_IPC_H
#define REVOLUTION_IPC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

s32 IOS_Open(const char* path, u32 mode);
s32 IOS_Close(s32 fd);

#ifdef __cplusplus
}
#endif

#endif
