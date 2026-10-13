#ifndef MEM_HEAPCOMPACTIONNODE_H
#define MEM_HEAPCOMPACTIONNODE_H

#include "mem/MemBlock.h"
#include "types.h"

namespace mem {

class HeapCompactionNode {
public:
    MemBlock block() const;
    u32 size() const;
    bool isFree() const;

    void setSize(u32 size);
    void setAddrAndSize(void* address, u32 size);
    void setIsFree(bool isFree);

private:
    void* mAddress;
    u32 mSize;
};

}  // namespace mem

#endif
