#ifndef MEM_HEAPCOMPACTION_H
#define MEM_HEAPCOMPACTION_H

#include "mem/HeapCompactionNodeHandle.h"
#include "mem/IAllocator.h"
#include "nrel/devkit/heapmap/IHeapMapUser.h"

namespace mem {

class HeapCompaction : public nrel::devkit::heapmap::IHeapMapUser, public IAllocator {
public:
    virtual ~HeapCompaction();
    virtual void* allocatorAlloc(u32 size, s32 align);
    virtual void allocatorFree(void* ptr);

    void compaction();
    HeapCompactionNodeHandle search(void* address);
};

}  // namespace mem

#endif
