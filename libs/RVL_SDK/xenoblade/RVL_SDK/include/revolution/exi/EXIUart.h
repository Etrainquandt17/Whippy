#ifndef RVL_SDK_EXI_UART_H
#define RVL_SDK_EXI_UART_H
#include <xenoblade/types.h>

#include <xenoblade/RVL_SDK/include/revolution/exi/EXICommon.h>
#ifdef __cplusplus
extern "C" {
#endif

void __OSEnableBarnacle(EXIChannel chan, u32 dev);

#ifdef __cplusplus
}
#endif
#endif
