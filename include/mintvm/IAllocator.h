#ifndef MINTVM_IALLOCATOR_H
#define MINTVM_IALLOCATOR_H

#include "types.h"

namespace mintvm {

class IAllocator {
public:
    virtual ~IAllocator() {}
    virtual void* mintAlloc(u32 size) = 0;
    virtual void mintFree(void* ptr) = 0;
};

}  // namespace mintvm

#endif
