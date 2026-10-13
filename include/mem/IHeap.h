#ifndef MEM_IHEAP_H
#define MEM_IHEAP_H

#include "mem/IAllocator.h"
#include "mem/MemBlock.h"
#include "types.h"

namespace mem {

class IHeap : public IAllocator {
public:
    virtual ~IHeap();
    virtual const char* heapName() const = 0;
    virtual MemBlock heapMemBlock() const = 0;
    virtual s32 heapUsingBlockCount() const = 0;
    virtual void heapDump() const = 0;
};

}  // namespace mem

#endif
