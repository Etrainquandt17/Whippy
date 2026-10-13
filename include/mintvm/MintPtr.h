#ifndef MINTVM_MINTPTR_H
#define MINTVM_MINTPTR_H

#include "mintvm/MintSystemCall.h"

namespace mintvm {

template <typename T>
class MintPtr {
public:
    T* ref() const {
        if (mPtr == 0) {
            MintSystemCall::messageHandler(MINT_MSG_ERROR, "MintPtr is 0.", "");
        }
        return mPtr;
    }

    T* operator->() const {
        return ref();
    }

private:
    T* mPtr;
};

}  // namespace mintvm

#endif
