#ifndef MEM_EXPLICITAUTODELETEARRAY_H
#define MEM_EXPLICITAUTODELETEARRAY_H

#include "types.h"

// TODO: the original's class, with its bodies, the range-checked array and the base. Units that were written
// against the declarations below call what this expands, so it is opt-in until they are done.
#ifdef MEM_EXPLICITAUTODELETEARRAY_INLINE

#include "hel/common/Array.h"
#include "hel/common/ArrayUtil.h"
#include "hel/common/NonCopyable.h"
#include "mem/IAllocator.h"

namespace mem {

template <typename T, int N>
class ExplicitAutoDeleteArray : private hel::common::NonCopyable {
public:
    ExplicitAutoDeleteArray(IAllocator& allocator) : mAllocator(&allocator), mCount(0), mArray() {}

    ~ExplicitAutoDeleteArray() { clear(); }

    void clear() {
        while (mCount != 0) {
            u32 last = mCount - 1;
            T* obj = mArray[last];
            mArray[last] = 0;
            mCount--;
            obj->~T();
            mAllocator->allocatorFree(obj);
        }
    }

    template <typename A1, typename A2>
    void add(A1 a1, A2 a2) {
        mArray[mCount] = new (*mAllocator) T(a1, a2);
        mCount++;
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5>
    void add(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) {
        mArray[mCount] = new (*mAllocator) T(a1, a2, a3, a4, a5);
        mCount++;
    }

    template <typename A1, typename A2, typename A3, typename A4>
    void add(A1 a1, A2 a2, A3 a3, A4 a4) {
        mArray[mCount] = new (*mAllocator) T(a1, a2, a3, a4);
        mCount++;
    }

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void add(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) {
        mArray[mCount] = new (*mAllocator) T(a1, a2, a3, a4, a5, a6);
        mCount++;
    }

    template <typename A1, typename A2, typename A3>
    void add(A1 a1, A2 a2, A3 a3) {
        mArray[mCount] = new (*mAllocator) T(a1, a2, a3);
        mCount++;
    }

    T& operator[](u32 index) {
        hel::common::ArrayUtil::RangeCheck(index, mCount);
        return *mArray[index];
    }
    const T& operator[](u32 index) const {
        hel::common::ArrayUtil::RangeCheck(index, mCount);
        return *mArray[index];
    }
    u32 count() const { return mCount; }

private:
    IAllocator* mAllocator;
    u32 mCount;
    hel::common::Array<T*, N> mArray;
};

}

#else

namespace mem {

class IAllocator;

template <typename T, int N>
class ExplicitAutoDeleteArray {
public:
    ExplicitAutoDeleteArray(IAllocator& allocator) : mAllocator(&allocator), mCount(0), mArray() {}
    ~ExplicitAutoDeleteArray();

    template <typename A1, typename A2, typename A3>
    void add(A1 a1, A2 a2, A3 a3);

    template <typename A1, typename A2, typename A3, typename A4>
    void add(A1 a1, A2 a2, A3 a3, A4 a4);

    template <typename A1, typename A2, typename A3, typename A4, typename A5>
    void add(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5);

    template <typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
    void add(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6);

    T& operator[](u32 index);
    const T& operator[](u32 index) const;
    u32 count() const { return mCount; }

private:
    IAllocator* mAllocator;
    // TODO: these two are a hel::common::MutableArray<T*, N>.
    u32 mCount;
    T* mArray[N];
};

}

#endif

#endif
