#ifndef INFO_HELP_MANAGER_H
#define INFO_HELP_MANAGER_H

#include "types.h"

namespace lyt {
class PaneAccessor;
}

namespace mem {
class IAllocator;
}

namespace info {
namespace help {

// TODO: the members and the other functions.
class Manager {
public:
    Manager(mem::IAllocator& allocator, const lyt::PaneAccessor& parent);
    ~Manager();

    bool isOpen() const;

private:
    u32 _0[0x215];
};

}}  // namespace info::help

#endif
