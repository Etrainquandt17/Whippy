#ifndef MEM_DATABLOCK_H
#define MEM_DATABLOCK_H

#include "mem/MemBlock.h"
#include "types.h"

namespace mem {

class IAllocator;

class DataBlock {
public:
    DataBlock(u32 size, s32 align, IAllocator& allocator);
    ~DataBlock();

    MemBlock block() const { return mBlock; }

private:
    IAllocator* mAllocator;
    MemBlock mBlock;
};

}

#endif
