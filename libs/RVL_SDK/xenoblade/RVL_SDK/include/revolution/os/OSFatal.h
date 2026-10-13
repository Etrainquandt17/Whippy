#ifndef RVL_SDK_OS_FATAL_H
#define RVL_SDK_OS_FATAL_H
#include <xenoblade/types.h>

#include <xenoblade/RVL_SDK/include/revolution/gx/GXTypes.h>
#ifdef __cplusplus
extern "C" {
#endif

void OSFatal(GXColor textColor, GXColor bgColor, const char* msg);

#ifdef __cplusplus
}
#endif
#endif
