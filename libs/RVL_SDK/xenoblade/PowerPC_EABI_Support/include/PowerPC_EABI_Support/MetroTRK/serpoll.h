#ifndef TRK_SERPOLL
#define TRK_SERPOLL

#include "xenoblade/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MetroTRK/dstypes.h"
#include "xenoblade/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C"{
#endif

extern void* gTRKInputPendingPtr;

void TRKGetInput();
void TRKProcessInput(int);
DSError TRKInitializeSerialHandler();
DSError TRKTerminateSerialHandler();

#ifdef __cplusplus
}
#endif
#endif
