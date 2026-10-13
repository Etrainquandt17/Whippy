#ifndef MINTVM_MVALUE_H
#define MINTVM_MVALUE_H

#include "types.h"

namespace mintvm {

union MValue {
    MValue& operator=(const MValue& other) {
        mU32 = other.mU32;
        return *this;
    }

    s32 mS32;
    u32 mU32;
    f32 mF32;
    bool mBool;
    void* mPtr;
    u32* mU32Ptr;
    s32* mS32Ptr;
    const unsigned int* mCode;
};

}  // namespace mintvm

#endif
