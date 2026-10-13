#ifndef MINTVM_MPTRARRAY_H
#define MINTVM_MPTRARRAY_H

#include "mintvm/IAllocator.h"
#include "mintvm/MintAssert.h"
#include "types.h"

namespace mintvm {

template <class T>
class MPtrArray {
public:
    MPtrArray(IAllocator& allocator, unsigned long max);
    ~MPtrArray();

    unsigned long count() const {
        return mCount;
    }

    T* at(unsigned long index) const {
        MINT_ASSERT_MSG("MPtrArray.hpp", 66, index < mCount, "count = %d\n", mCount);
        return mData[index];
    }

    T* at(unsigned long index) {
        MINT_ASSERT_MSG("MPtrArray.hpp", 71, index < mCount, "count = %d\n", mCount);
        return mData[index];
    }

    void add(T* ptr) {
        addPtr(ptr);
    }

    void deletePtr(unsigned long index) {
        MINT_ASSERT("MPtrArray.hpp", 118, index < mCount);
        MINT_ASSERT("MPtrArray.hpp", 119, mData[index]);
        delete mData[index];
        mData[index] = 0;
    }

    void addPtr(T* ptr) {
        MINT_ASSERT_MSG("MPtrArray.hpp", 111, mCount < mMax, "mMax = %d\n", mMax);
        mData[mCount] = ptr;
        mCount++;
    }

private:
    IAllocator& mAllocator;
    unsigned long mMax;
    unsigned long mCount;
    T** mData;
};

template <class T>
inline MPtrArray<T>::MPtrArray(IAllocator& allocator, unsigned long max)
    : mAllocator(allocator)
    , mMax(max)
    , mCount(0)
    , mData(0) {
    mData = static_cast<T**>(allocator.mintAlloc(max * sizeof(T*)));
    for (unsigned long i = 0; i < mMax; i++) {
        mData[i] = 0;
    }
}

template <class T>
inline MPtrArray<T>::~MPtrArray() {
    for (unsigned long i = mCount; i != 0; i--) {
        deletePtr(i - 1);
    }
    mAllocator.mintFree(mData);
}

}  // namespace mintvm

#endif
