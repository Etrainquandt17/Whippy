#ifndef METROTRK_DISPATCH
#define METROTRK_DISPATCH

#include "xenoblade/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MetroTRK/trk.h"
#include "xenoblade/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MetroTRK/msgbuf.h"

#ifdef __cplusplus
extern "C"{
#endif

DSError TRK_DispatchMessage(MessageBuffer*);

#ifdef __cplusplus
}
#endif
#endif
