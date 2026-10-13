#include "mem/AutoHeapExp.h"

namespace mem {

AutoHeapExp::AutoHeapExp(IAllocator& allocator, u32 size, const char* name)
    : DataBlock(size, 4, allocator)
    , mObj(hel::common::FixedString<32>(name), block(), false, false) {}

HeapExp& AutoHeapExp::obj() {
    return mObj;
}

}
