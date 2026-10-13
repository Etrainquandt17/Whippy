#ifndef RVL_SDK_VI_VI3IN1_H
#define RVL_SDK_VI_VI3IN1_H
#include <xenoblade/types.h>
#include <xenoblade/RVL_SDK/include/revolution/vi/vitypes.h>
#ifdef __cplusplus
extern "C" {
#endif

void __VISetRGBModeImm(void);

void __VISetRevolutionModeSimple(void);

void VISetGamma(VIGamma gamma);
void VISetTrapFilter(VIBool filter);

#ifdef __cplusplus
}
#endif
#endif
