#ifndef EFFECT_GROUP_H
#define EFFECT_GROUP_H

#include "types.h"

namespace mem {
class IAllocator;
}

namespace effect {

class Manager;

class Group {
public:
    Group(Manager& manager);
    Group(Manager& manager, mem::IAllocator& allocator, u32);
    ~Group();

private:
    u32 _0[0xC];
};

}

#endif
