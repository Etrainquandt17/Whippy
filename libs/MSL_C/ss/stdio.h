#ifndef MSL_STDIO_H_
#define MSL_STDIO_H_

#include <ss/cstdio>
#include <ss/stddef.h>
#include <ss/stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace std {
    using ::fputs;
    using ::fflush;
    using ::fclose;
    using ::fprintf;
    using ::printf;
    using ::sprintf;
    using ::snprintf;
    using ::vsnprintf;
    using ::vprintf;
    using ::vswprintf;
    using ::sscanf;
}

#ifdef __cplusplus
};
#endif

#endif
