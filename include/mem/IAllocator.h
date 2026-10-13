#ifndef MEM_IALLOCATOR_H
#define MEM_IALLOCATOR_H

#include "types.h"

namespace mem {

class IAllocator {
public:
    virtual ~IAllocator();
    virtual void* allocatorAlloc(u32 size, s32 align) = 0;
    virtual void allocatorFree(void* ptr) = 0;
};

}

void* operator new(u32 size, mem::IAllocator& allocator);

#endif
