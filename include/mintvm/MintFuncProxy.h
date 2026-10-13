#ifndef MINTVM_MINTFUNCPROXY_H
#define MINTVM_MINTFUNCPROXY_H

#include "mintvm/MValue.h"
#include "mintvm/MintAssert.h"
#include "mintvm/Regset.h"
#include "types.h"

namespace mintvm {

class MintFuncProxy {
public:
    MintFuncProxy(Regset& regset, bool flag)
        : mRegset(&regset)
        , mUseRetVal(false)
        , mUseThis(false)
        , _6(flag)
        , mOffset(0) {}

    ~MintFuncProxy() {}

    void useRetVal() {
        mUseRetVal = true;
        setupOffset();
    }

    void useThis() {
        mUseThis = true;
        setupOffset();
    }

    void setupOffset() {
        mOffset = (mUseRetVal ? 1 : 0) + (mUseThis ? 1 : 0);
    }

    int getArg_s32(unsigned int index) const {
        return mRegset->getFR(index + mOffset).mS32;
    }

    float getArg_f32(unsigned int index) const {
        return mRegset->getFR(index + mOffset).mF32;
    }

    const char* getArg_string(unsigned int index) const {
        return static_cast<const char*>(mRegset->getFR(index + mOffset).mPtr);
    }

    // TODO: the name is a guess; the function is inlined wherever it is used.
    bool getArg_bool(unsigned int index) const {
        return mRegset->getFR(index + mOffset).mBool;
    }

    // TODO: the name is a guess; the function is inlined wherever it is used.
    void setArg_s32(unsigned int index, int value) {
        mRegset->internal_getFR(index + mOffset).mS32 = value;
    }

    void setRet_s32(int value) {
        MINT_ASSERT("MintFuncProxy.hpp", 89, mUseRetVal);
        mRegset->internal_getFR(0).mS32 = value;
    }

    void setRet_f32(float value) {
        MINT_ASSERT("MintFuncProxy.hpp", 90, mUseRetVal);
        mRegset->internal_getFR(0).mF32 = value;
    }

    MValue* internal_getArg_addr(unsigned int index) const {
        return &mRegset->internal_getFR(index + mOffset);
    }

    void* internal_getRet_addr() const {
        MINT_ASSERT("MintFuncProxy.hpp", 146, mUseRetVal);
        if (_6) {
            return mRegset->internal_getFR(0).mPtr;
        }
        return &mRegset->internal_getFR(0);
    }

    template <typename T>
    T& getThis() {
        return *static_cast<T*>(mRegset->getFR(mOffset - 1).mPtr);
    }

    Regset* mRegset;
    bool mUseRetVal;
    bool mUseThis;
    bool _6;
    u32 mOffset;
};

}  // namespace mintvm

#endif
