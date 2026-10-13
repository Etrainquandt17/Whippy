#ifndef METROTRK_NOTIFY
#define METROTRK_NOTIFY

#include "xenoblade/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MetroTRK/dstypes.h"
#include "xenoblade/PowerPC_EABI_Support/include/PowerPC_EABI_Support/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C"{
#endif

DSError TRKDoNotifyStopped(MessageCommandID);

#ifdef __cplusplus
}
#endif
#endif
