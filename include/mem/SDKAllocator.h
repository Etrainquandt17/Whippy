#ifndef MEM_SDKALLOCATOR_H
#define MEM_SDKALLOCATOR_H

#include "types.h"

namespace mem {

class IAllocator;

class SDKAllocator {
public:
    SDKAllocator(IAllocator& allocator, int align);

private:
    u32 _0[6];
};

}  // namespace mem

#endif
