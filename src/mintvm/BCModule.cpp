#include "mintvm/BCModule.h"

#include "mintvm/stdc.h"

namespace mintvm {

// TODO: the linker removed this function from the game, so its body is not known. This one only
// makes the compiler emit the three functions of XData that the original did not inline.
void BCModule::dump(const mintx::XData& data) {
    if (!data.isValidData()) {
        return;
    }
    printf(data.R2String(mName));
    const BCSymbolTable* symbols = static_cast<const BCSymbolTable*>(data.labelAddressWithReference(mSymbolTable));
    for (u32 i = 0; i < symbols->mCount; i++) {
        printf(data.R2String(symbols->mSymbols[i]));
    }
    printf(static_cast<const char*>(data.labelAddressWithReference(mName)));
}

}
