#ifndef MEM_HEAPUNIT_H
#define MEM_HEAPUNIT_H

#include "hel/common/FixedString.h"
#include "mem/IAllocator.h"
#include "mem/MemBlock.h"
#include "types.h"

namespace mem {

class HeapUnit : public IAllocator {
public:
    HeapUnit(const hel::common::FixedString<32>& name, IAllocator& allocator, unsigned long blockSize, unsigned long blockCount, int align);
    virtual ~HeapUnit();

    virtual void* allocatorAlloc(u32 size, s32 align);
    virtual void allocatorFree(void* ptr);
    // TODO: the virtual functions that follow (heapName, heapMemBlock, heapUsingBlockCount, heapDump).

    void* alloc(unsigned long size);
    void* alloc(unsigned long size, long align);
    void free(void* ptr);

    u32 memBlockSize() const;
    u32 freeMemBlockCount() const { return mMemBlockCount - mUsingBlockCount; }

    // TODO: the names of these two are guesses; they are inlined wherever they are used.
    bool isFull() const { return mUsingBlockCount == mMemBlockCount; }
    MemBlock memBlock() const { return mMemBlock; }

private:
    hel::common::FixedString<32> mName;
    u32 mMemBlockSize;
    u32 mMemBlockCount;
    s32 mAlign;
    u32 _30;
    MemBlock mMemBlock;
    u32 mUsingBlockCount;
    u32 mPeakUsingBlockCount;
    void* mHeapHandle;
    u32 _48;
    u32 _4C;
    u32 _50;
};

}  // namespace mem

#endif
