#ifndef MSL_PPC_EABI_ABORT_EXIST_PPC_EABI_H
#define MSL_PPC_EABI_ABORT_EXIST_PPC_EABI_H
#include <kdc/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void abort();

extern int __stdio_exit;
extern BOOL __aborting;

#ifdef __cplusplus
}
#endif
#endif
