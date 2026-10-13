#include "mem/MemBlock.h"

namespace mem {

MemBlock MemBlock::EmptyBlock() {
    return MemBlock(0, 0);
}

MemBlock::MemBlock(void* address, u32 size)
    : mSize(size)
    , mAddress(address) {}

}
