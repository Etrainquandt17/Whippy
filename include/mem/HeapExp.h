#ifndef MEM_HEAPEXP_H
#define MEM_HEAPEXP_H

#include "hel/common/FixedString.h"
#include "mem/IAllocator.h"
#include "mem/IHeap.h"
#include "mem/MemBlock.h"
#include "nrel/devkit/heapmap/ExpHeapMapUser.h"
#include "revolution/mem.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace mem {

class HeapExp : public IHeap {
public:
    class AllocFromTailAllocator : public IAllocator {
    public:
        AllocFromTailAllocator(HeapExp& heap);
        virtual void* allocatorAlloc(u32 size, s32 align);
        virtual void allocatorFree(void* ptr);

    private:
        HeapExp& mHeap;
    };

    virtual ~HeapExp();
    virtual void* allocatorAlloc(u32 size, s32 align);
    virtual void allocatorFree(void* ptr);
    virtual const char* heapName() const;
    virtual MemBlock heapMemBlock() const;
    virtual s32 heapUsingBlockCount() const;
    virtual void heapDump() const;

    HeapExp(const hel::common::FixedString<32>& name, const MemBlock& block, bool noHeapMap, bool noFill);

    void* alloc(unsigned long size);
    void* alloc(unsigned long size, long align);
    void* alloc(unsigned long size, long align, bool fromTail);
    void free(void* address);

    IAllocator& allocFromHeadAllocator();
    IAllocator& allocFromTailAllocator();

private:
    hel::common::FixedString<32> mName;
    MemBlock mBlock;
    s32 mUsingBlockCount;
    bool mNoFill;
    MEMiHeapHead* mHeap;
    util::PlacementNew<nrel::devkit::heapmap::ExpHeapMapUser> mMapUser;
    util::PlacementNew<AllocFromTailAllocator> mTailAllocator;
};

}

#endif
