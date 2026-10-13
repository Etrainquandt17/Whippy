#ifndef HEL_COMMON_TRAITS_H
#define HEL_COMMON_TRAITS_H

#include "types.h"

namespace hel {
namespace common {

template <typename T>
class Traits {
public:
    static void Strncpy(T* dst, const T* src, u32 size);
    static u32 Strlen(const T* str);
};

}
}

#endif
