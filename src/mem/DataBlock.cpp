#include "mem/DataBlock.h"

#include "mem/IAllocator.h"

namespace mem {

DataBlock::DataBlock(u32 size, s32 align, IAllocator& allocator)
    : mAllocator(&allocator)
    , mBlock(allocator.allocatorAlloc(size, align), size) {}

DataBlock::~DataBlock() {
    mAllocator->allocatorFree(mBlock.startAddress());
}

}  // namespace mem
