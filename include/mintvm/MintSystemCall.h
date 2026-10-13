#ifndef MINTVM_MINTSYSTEMCALL_H
#define MINTVM_MINTSYSTEMCALL_H

#include "mintvm/MintAssert.h"
#include "mintvm/MintSetting.h"

namespace mintvm {

namespace MintSystemCall {

void halt();
void messageHandler(MintMsgKind kind, const char* message, const char* detail);

}

}  // namespace mintvm

#endif
