#ifndef INFO_COMMON_LOWBATTERY_H
#define INFO_COMMON_LOWBATTERY_H

#include "lyt/Layout.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace info {
namespace common {

class LowBattery {
public:
    LowBattery(mem::IAllocator& allocator, u32);

private:
    lyt::Layout mLayout;
    u32 _190[3];
};

}}  // namespace info::common

#endif
