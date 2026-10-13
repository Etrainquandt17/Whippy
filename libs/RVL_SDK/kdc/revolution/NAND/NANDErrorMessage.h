#ifndef RVL_SDK_NAND_ERROR_MESSAGE_H
#define RVL_SDK_NAND_ERROR_MESSAGE_H
#include <kdc/types.h>

#include <kdc/revolution/NAND/nand.h>
#ifdef __cplusplus
extern "C" {
#endif

void NANDSetAutoErrorMessaging(BOOL);
void __NANDPrintErrorMessage(s32);

#ifdef __cplusplus
}
#endif
#endif
