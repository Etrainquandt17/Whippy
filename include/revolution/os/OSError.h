#ifndef REVOLUTION_OS_OSERROR_H
#define REVOLUTION_OS_OSERROR_H

#ifdef __cplusplus
extern "C" {
#endif

void OSPanic(const char* file, int line, const char* message, ...);

#ifdef __cplusplus
}
#endif

#endif
