#ifndef REVOLUTION_SC_H
#define REVOLUTION_SC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

u32 SCCheckStatus(void);
u8 SCGetAspectRatio(void);
u8 SCGetEuRgb60Mode(void);
u8 SCGetLanguage(void);
u8 SCGetProgressiveMode(void);

#ifdef __cplusplus
}
#endif

#endif
