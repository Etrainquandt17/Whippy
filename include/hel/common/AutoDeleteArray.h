#ifndef HEL_COMMON_AUTODELETEARRAY_H
#define HEL_COMMON_AUTODELETEARRAY_H

#include "hel/common/ArrayUtil.h"
#include "types.h"
#ifdef HEL_COMMON_AUTODELETEARRAY_INLINE
#include "hel/common/Array.h"
#include "hel/common/NonCopyable.h"
#endif

namespace hel {
namespace common {

#ifdef HEL_COMMON_AUTODELETEARRAY_INLINE
// The original's bodies, as scn/subgame/common/input/NewEntryErrorManager.cpp emits them. Opt-in until the units
// written against the declarations below are compared with it.
template <typename T, int N>
class AutoDeleteArray : private NonCopyable {
public:
    AutoDeleteArray() : mCount(0), mArray() {}
    ~AutoDeleteArray() {
        while (mCount != 0) {
            T* object;
            u32 index = mCount - 1;
            object = mArray[index];
            mArray[index] = 0;
            mCount--;
            delete object;
        }
    }

    void add(T* object) {
        mArray[mCount] = object;
        mCount++;
    }
    u32 count() const { return mCount; }

    T& operator[](u32 index) { return *mArray[index]; }
    T& operator[](u32 index) const { return *mArray[index]; }

private:
    u32 mCount;
    Array<T*, N> mArray;
};
#else
template <typename T, int N>
class AutoDeleteArray {
public:
    AutoDeleteArray();
    ~AutoDeleteArray();

    void add(T* object);

    T** begin() { return mArray; }
    T** end();

    T& operator[](u32 index) const {
        ArrayUtil::RangeCheck(index, N);
        return *mArray[index];
    }

private:
    // TODO: these two are a hel::common::MutableArray<T*, N>; the destructor
    // ends with a base destructor call on the whole object.
    u32 mCount;
    T* mArray[N];
};
#endif

}
}

#endif
