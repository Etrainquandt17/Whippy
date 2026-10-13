#ifndef HEL_COMMON_ARRAY_H
#define HEL_COMMON_ARRAY_H

#include "hel/common/ArrayUtil.h"
#include "types.h"

namespace hel {
namespace common {

template <typename T, int N>
class Array {
public:
    Array() : mArray() {}

    T& operator[](u32 index) {
        ArrayUtil::RangeCheck(index, N);
        return mArray[index];
    }
    const T& operator[](u32 index) const {
        ArrayUtil::RangeCheck(index, N);
        return mArray[index];
    }

private:
    T mArray[N];
};

}
}

#endif
