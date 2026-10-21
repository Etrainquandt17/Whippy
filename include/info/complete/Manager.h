#ifndef INFO_COMPLETE_MANAGER_H
#define INFO_COMPLETE_MANAGER_H

#include "types.h"

namespace mem {
class IAllocator;
}

namespace info {
namespace complete {

// TODO: the members and the other functions.
class Manager {
public:
    Manager(mem::IAllocator& allocator, const bool&);
    ~Manager();

    void open();
    bool isEnd() const;

private:
    u32 _0[0x69];
};

}}  // namespace info::complete

#endif
