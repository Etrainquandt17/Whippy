#ifndef RVL_SDK_OS_FATAL_H
#define RVL_SDK_OS_FATAL_H
#include <kdc/types.h>

#include <kdc/revolution/GX/GXTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

void OSFatal(GXColor textColor, GXColor bgColor, const char* msg);

#ifdef __cplusplus
}
#endif
#endif
