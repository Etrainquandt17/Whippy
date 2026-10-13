#ifndef _MSL_WPRINTF_H
#define _MSL_WPRINTF_H

#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/file_def.h"
#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/restrict_def.h"
#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h"
#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/wchar_def.h"
#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/va_list_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int wprintf(const wchar_t *RESTRICT format, ...);
int fwprintf(FILE *RESTRICT stream, const wchar_t *RESTRICT format, ...);
int swprintf(wchar_t *RESTRICT buffer, size_t bufsz, const wchar_t *RESTRICT format, ...);

int vwprintf(const wchar_t *RESTRICT format, va_list vlist);
int vfwprintf(FILE *RESTRICT stream, const wchar_t *RESTRICT format, va_list vlist);
int vswprintf(
    wchar_t *RESTRICT buffer, size_t bufsz, const wchar_t *RESTRICT format, va_list vlist
);

#ifdef __cplusplus
}
#endif

#endif
