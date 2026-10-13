#ifndef MSL_WPRINTF_H
#define MSL_WPRINTF_H

#include <xenoblade/types.h>
#include <xenoblade/PowerPC_EABI_Support/include/stl/stdarg.h>
#include <xenoblade/PowerPC_EABI_Support/include/stl/stdio.h>

//wprintf
//wprintf_s
//fwprintf
//fwprintf_s
//vwprintf
//vwprintf_s
//vfwprintf
//vfwprintf_s
int swprintf(wchar_t*, size_t, const wchar_t*, ...);
//swprintf_s
//snwprintf_s
int vswprintf(wchar_t*, size_t, const wchar_t*, va_list);
//vswprintf_s
//vsnwprintf_s

#endif
