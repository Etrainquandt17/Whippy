#include "mintvm/MintSystemCall.h"

#include "mintvm/stdc.h"

namespace mintvm {

namespace MintSystemCall {

void panic(const char* file, int line, const char* message, ...) {
    va_list args;
    va_start(args, message);
    vprintf(message, args);
    va_end(args);

    printf("[Mint_Panic] file \"%s\" : line %d.\n", file, line);
    halt();
}

void halt() {
    MintSetting::Instance()->mHaltCallback();
}

void messageHandler(MintMsgKind kind, const char* message, const char* detail) {
    MintSetting* setting = MintSetting::Instance();
    setting->mMessageCallback(kind, message, detail);
    if (kind >= MINT_MSG_ERROR) {
        halt();
    }
}

}

}
