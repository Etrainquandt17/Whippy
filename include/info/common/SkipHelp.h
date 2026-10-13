#ifndef INFO_COMMON_SKIPHELP_H
#define INFO_COMMON_SKIPHELP_H

#include "lyt/Layout.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace info {
namespace common {

class SkipHelp {
public:
    SkipHelp(mem::IAllocator& allocator);

private:
    lyt::Layout mLayout;
    u32 _190[4];
};

}}  // namespace info::common

#endif
