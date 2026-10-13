#ifndef MINTVM_VMFUNCTION_H
#define MINTVM_VMFUNCTION_H

#include "mintvm/BCModule.h"
#include "mintvm/MintAssert.h"
#include "mintvm/VMObject.h"
#include "mintvm/XData.h"
#include "types.h"

namespace mintvm {

class MintFuncProxy;

class VMFunction : public VMObject {
public:
    enum Kind {
        KIND_MINT,
        KIND_NATIVE,
    };

    typedef void (*NativeFunc)(MintFuncProxy&);

    VMFunction(const mintx::XData& data, const BCFunction* function)
        : mKind(KIND_MINT)
        , mName(data.R2String(function->mName) + 4)
        , mIsBuiltInReturn(false) {
        mInstruction = static_cast<const unsigned int*>(data.labelAddressWithReference(function->mInstruction));
        setup();
    }

    VMFunction(const char* name, NativeFunc func)
        : mKind(KIND_NATIVE)
        , mName(name)
        , mIsBuiltInReturn(false) {
        mNativeFunc = func;
        setup();
    }

    virtual ~VMFunction() {}

    void setup();
    void parseName();

    bool isMint() const {
        return mKind == KIND_MINT;
    }

    const unsigned int* instruction() const {
        MINT_ASSERT("VMFunction.hpp", 59, isMint());
        return mInstruction;
    }

    bool isNative() const {
        return mKind == KIND_NATIVE;
    }

    NativeFunc nativeFunc() const {
        MINT_ASSERT("VMFunction.hpp", 60, isNative());
        return mNativeFunc;
    }

    bool isBuiltInReturn() const {
        return mIsBuiltInReturn;
    }

    const char* name() const {
        return mName;
    }

private:
    Kind mKind;
    const char* mName;
    bool mIsBuiltInReturn;
    union {
        const unsigned int* mInstruction;
        NativeFunc mNativeFunc;
    };
};

}

#endif
