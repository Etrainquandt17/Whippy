#ifndef OCOLL_OWNER_H
#define OCOLL_OWNER_H

#include "types.h"

namespace mem {
class IAllocator;
}

namespace ocoll {

class Manager;

class Owner {
public:
    Owner(Manager& manager, u32, mem::IAllocator& allocator);
    ~Owner();

    u64 uid() const;
    u64 rootUid() const;
    void setParentInterim(Owner& parent);
    void unsetParentInterim();
    u32 teamNo() const;

private:
    u8 _0[0x30];
};

}

#endif
