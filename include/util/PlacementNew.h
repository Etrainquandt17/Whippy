#ifndef UTIL_PLACEMENTNEW_H
#define UTIL_PLACEMENTNEW_H

#include "std/new.h"
#include "types.h"

namespace util {

template <typename T>
class PlacementNew {
public:
    PlacementNew() : mObj(0) {}
    ~PlacementNew() { destruct(); }

    void destruct() {
        if (mObj != 0) {
            mObj->~T();
            mObj = 0;
        }
    }

    void construct() {
        destruct();
        mObj = new (mBuffer) T;
    }

    template <typename A1>
    void construct(A1 a1) {
        destruct();
        mObj = new (mBuffer) T(a1);
    }

    template <typename A1, typename A2>
    void construct(A1 a1, A2 a2) {
        destruct();
        mObj = new (mBuffer) T(a1, a2);
    }

    template <typename A1, typename A2, typename A3>
    void construct(A1 a1, A2 a2, A3 a3) {
        destruct();
        mObj = new (mBuffer) T(a1, a2, a3);
    }

    bool isConstruct() const { return mObj != 0; }
    // TODO: how the original reaches the object is not known; both are only seen inlined.
    T* operator->() const { return mObj; }
    T& operator*() const { return *mObj; }

private:
    T* mObj;
    u8 mBuffer[sizeof(T)];
};

}  // namespace util

#endif
