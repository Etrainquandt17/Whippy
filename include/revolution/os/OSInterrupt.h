#ifndef REVOLUTION_OS_OSINTERRUPT_H
#define REVOLUTION_OS_OSINTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

int OSDisableInterrupts(void);
int OSRestoreInterrupts(int enabled);

#ifdef __cplusplus
}
#endif

#endif
