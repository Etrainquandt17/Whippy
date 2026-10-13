#ifndef HEL_COMMON_AUTODELETEARRAY_H
#define HEL_COMMON_AUTODELETEARRAY_H

#include "types.h"

namespace hel {
namespace common {

template <typename T, int N>
class AutoDeleteArray {
public:
    AutoDeleteArray();
    ~AutoDeleteArray();

    void add(T* object);

    T** begin() { return mArray; }
    T** end();

private:
    // TODO: these two are a hel::common::MutableArray<T*, N>; the destructor
    // ends with a base destructor call on the whole object.
    u32 mCount;
    T* mArray[N];
};

}
}

#endif
