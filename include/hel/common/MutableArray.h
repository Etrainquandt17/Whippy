#ifndef HEL_COMMON_MUTABLEARRAY_H
#define HEL_COMMON_MUTABLEARRAY_H

#include "hel/common/Array.h"
#include "hel/common/ArrayUtil.h"
#include "std/for_each.h"
#include "types.h"

namespace hel {
namespace common {

// TODO: add() belongs in the class body, where it is emitted at its first use (info/sequence/Sequence.cpp
// needs that and defines HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS). Linked units match with it below the class.
template <typename T, int N>
class MutableArray {
public:
    MutableArray() : mCount(0), mArray() {}
    // TODO: the empty body is the original's: a local array is destroyed without a call, a member with one
    // (scn/step/gimmick/popflower/PopFlower.cpp). It is opt-in for the units written with the declaration.
#ifdef HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
    ~MutableArray() {}
#else
    ~MutableArray();
#endif

    u32 count() const { return mCount; }
    // TODO: name. Only seen inlined.
    bool isFull() const { return mCount == N; }

#ifdef HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
    void add(const T& value) {
        if (!isFull()) {
            mArray[mCount] = value;
            mCount++;
        }
    }
#else
    void add(const T& value);
#endif
    // TODO: the body is the original's (scn/step/gimmick/popflower/PopFlower.cpp emits it at its first use). It is
    // opt-in for the units that were written while the header only declared it.
#ifdef HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS
    void removeAtIndex(u32 index) {
        if (mCount > index) {
            for (u32 i = index + 1; i < count(); i++) {
                mArray[i - 1] = mArray[i];
            }
            mCount--;
        }
    }
#else
    void removeAtIndex(u32 index);
#endif

    T& operator[](u32 index) {
        ArrayUtil::RangeCheck(index, mCount);
        return mArray[index];
    }
    const T& operator[](u32 index) const {
        ArrayUtil::RangeCheck(index, mCount);
        return mArray[index];
    }

    T& at(u32 index) {
        ArrayUtil::RangeCheck(index, mCount);
        return mArray[index];
    }
    const T& at(u32 index) const {
        ArrayUtil::RangeCheck(index, mCount);
        return mArray[index];
    }

    // TODO: names. Both are only seen inlined, in scn::step::spstop::Manager.
    u32 find(const T& value) const {
        for (u32 i = 0; i < mCount; i++) {
            if (value == (*this)[i]) {
                return i;
            }
        }
        return -1;
    }
    void erase(u32 index) {
        if (mCount > index) {
            for (u32 i = index + 1; i < count(); i++) {
                mArray[i - 1] = mArray[i];
            }
            mCount--;
        }
    }

    // TODO: names. All four are only seen inlined, in info::sequence::Sequence. The functor is copied once
    // more than std::for_each alone would copy it.
    T* begin() { return reinterpret_cast<T*>(&mArray); }
    T* end() { return begin() + mCount; }
    template <class F>
    void forEach(F f) {
        std::for_each(begin(), end(), f);
    }
    void clear() { mCount = 0; }

private:
    u32 mCount;
    Array<T, N> mArray;
};

#ifndef HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
template <typename T, int N>
void MutableArray<T, N>::add(const T& value) {
    if (!isFull()) {
        mArray[mCount] = value;
        mCount++;
    }
}
#endif

}
}

#endif
