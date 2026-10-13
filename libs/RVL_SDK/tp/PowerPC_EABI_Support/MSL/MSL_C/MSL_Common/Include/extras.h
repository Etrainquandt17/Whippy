#ifndef _MSL_COMMON_EXTRAS_H
#define _MSL_COMMON_EXTRAS_H

#include <tp/PowerPC_EABI_Support/MSL/MSL_C/MSL_Common/Include/cstddef>

#ifdef __cplusplus
extern "C" {
#endif

int strnicmp(const char* str1, const char* str2, int n);
int stricmp(const char* str1, const char* str2);
size_t wcslen(const wchar_t* s);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_EXTRAS_H */
