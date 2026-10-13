#ifndef MINTVM_VMTMPKEY_H
#define MINTVM_VMTMPKEY_H

#include "mintvm/TmpSymbol.h"
#include "mintvm/VMKey.h"

namespace mintvm {

// A key that owns its text: "Ns.Sub.name(args)" is split at the last dot.
class VMTmpKey : public VMKey {
public:
    VMTmpKey(const char* symbol)
        : VMKey("", "")
        , mSymbol(symbol) {
        int paren = TmpSymbol::find(mSymbol.c_str(), '(');
        char* parenPtr = 0;
        if (paren != -1) {
            parenPtr = &mSymbol.buffer()[paren];
            mSymbol.divide(paren);
        }
        int dot = mSymbol.rfind('.');
        if (parenPtr != 0) {
            *parenPtr = '(';
        }
        setName(mSymbol.divide(dot));
        setNs(mSymbol.c_str());
    }

    ~VMTmpKey() {}

private:
    TmpSymbol mSymbol;
};

}

#endif
