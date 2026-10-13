#ifndef HEL_COMMON_RUNTIMETYPEINFOIMPL_H
#define HEL_COMMON_RUNTIMETYPEINFOIMPL_H

#include "hel/common/RuntimeTypeInfo.h"

namespace hel {
namespace common {

// TODO: this belongs in RuntimeTypeInfo.h. It is apart because a unit that sees it makes an info of its own for
// every class whose header does not declare a specialisation, and most headers do not yet.
template <typename T>
const RuntimeTypeInfo& RuntimeTypeInfoImpl() {
    static RuntimeTypeInfo ti(0, RuntimeTypeInfo::NoName());
    return ti;
}

}
}

#endif
