#ifndef HEL_COMMON_ARRAYUTIL_H
#define HEL_COMMON_ARRAYUTIL_H

#include "types.h"

namespace hel {
namespace common {

class ArrayUtil {
public:
    static void RangeCheck(u32 index, u32 count);
};

}
}

#endif
