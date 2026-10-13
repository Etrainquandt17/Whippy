#ifndef HEL_COMMON_RUNTIMETYPEINFOINLINE_H
#define HEL_COMMON_RUNTIMETYPEINFOINLINE_H

#include "hel/common/RuntimeTypeInfo.h"

namespace hel {
namespace common {

// TODO: this belongs in the class. It is apart because seq/SequenceWMapRoot.cpp, which is partly written,
// calls it once so far and would expand it where the original keeps a call.
inline bool RuntimeTypeInfo::isDerivedFrom(const RuntimeTypeInfo& other) const {
    for (const RuntimeTypeInfo* info = this; info != 0; info = info->mParent) {
        if (info == &other) {
            return true;
        }
    }
    return false;
}

}}  // namespace hel::common

#endif
