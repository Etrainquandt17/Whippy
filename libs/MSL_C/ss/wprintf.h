#ifndef _MSL_COMMON_WPRINTF_H
#define _MSL_COMMON_WPRINTF_H

#include <ss/wstring.h>
#include <ss/cstddef>
#include <ss/cstdarg>

#ifdef __cplusplus
extern "C" {
#endif

int swprintf(wchar_t *dst, size_t maxlen, const wchar_t *fmt, ...);

int vsnwprintf_s(wchar_t* str, size_t n, const wchar_t* fmt, va_list args);

#ifdef __cplusplus
}
#endif

#endif /* _MSL_COMMON_WPRINTF_H */
