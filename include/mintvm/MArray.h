#ifndef MINTVM_MARRAY_H
#define MINTVM_MARRAY_H

#include "mintvm/IAllocator.h"
#include "mintvm/MintAssert.h"
#include "std/new.h"
#include "types.h"

namespace mintvm {

template <class T>
class MArray {
public:
    MArray(IAllocator& allocator, unsigned long count)
        : mAllocator(allocator)
        , mCount(count)
        , mData(0) {
        if (mCount == 0) {
            return;
        }
        mData = static_cast<T*>(allocator.mintAlloc(count * sizeof(T)));
        for (unsigned long i = 0; i < mCount; i++) {
            new (&mData[i]) T();
        }
    }

    ~MArray() {
        if (mCount != 0) {
            mAllocator.mintFree(mData);
        }
    }

    unsigned long count() {
        return mCount;
    }

    unsigned long count() const {
        return mCount;
    }

    const T& at(unsigned long index) const {
        MINT_ASSERT_MSG("MArray.hpp", 73, index < mCount, "index = %d, count = %d\n", index, mCount);
        return mData[index];
    }

    T& at(unsigned long index) {
        MINT_ASSERT_MSG("MArray.hpp", 78, index < mCount, "index = %d, count = %d\n", index, mCount);
        return mData[index];
    }

    T& operator[](unsigned long index) {
        return at(index);
    }

    const T& operator[](unsigned long index) const {
        return at(index);
    }

private:
    IAllocator& mAllocator;
    unsigned long mCount;
    T* mData;
};

}

#endif
