#ifndef _MSL_WCHAR_TIME_H
#define _MSL_WCHAR_TIME_H

#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/size_def.h"
#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/time_def.h"
#include "key/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t wcsftime(wchar_t *str, size_t count, const wchar_t *format, struct tm *time);

#ifdef __cplusplus
}
#endif

#endif
