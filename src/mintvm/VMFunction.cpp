#include "mintvm/VMFunction.h"

#include "mintvm/MintSystemCall.h"
#include "mintvm/TmpSymbol.h"
#include "mintvm/VMCore.h"

namespace mintvm {

void VMFunction::setup() {
    parseName();
}

void VMFunction::parseName() {
    TmpSymbol symbol(name());
    if (symbol.find(' ') != -1) {
        int index = symbol.find(' ');
        if (index >= 0) {
            symbol.divide(index);
        }
        mIsBuiltInReturn = VMCore::isBuiltInType(symbol.c_str());
    } else {
        mIsBuiltInReturn = true;
        MintSystemCall::messageHandler(MINT_MSG_WARNING, "VMFunction::parseName fail", TmpSymbol("Not Found ReturnType '", name(), "' (ex. 'void Assert(int)')").c_str());
    }
}

}
