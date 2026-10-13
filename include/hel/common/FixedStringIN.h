#ifndef HEL_COMMON_FIXEDSTRINGIN_H
#define HEL_COMMON_FIXEDSTRINGIN_H

#include "hel/common/Traits.h"
#include "types.h"

namespace hel {
namespace common {

template <typename T, int N>
class FixedStringIN {
public:
    FixedStringIN() : mStr() { mStr[0] = 0; }
    FixedStringIN(const T* str) : mStr() { Traits<T>::Strncpy(mStr, str, N); }

    static FixedStringIN FromFormat(const T* format, ...);

    operator const T*() const { return mStr; }

private:
    T mStr[N];
};

}
}

#endif
