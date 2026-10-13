#ifndef MEM_AUTOHEAPEXP_H
#define MEM_AUTOHEAPEXP_H

#include "mem/DataBlock.h"
#include "mem/HeapExp.h"
#include "types.h"

namespace mem {

class IAllocator;

class AutoHeapExp : public DataBlock {
public:
    AutoHeapExp(IAllocator& allocator, u32 size, const char* name);
    ~AutoHeapExp();

    HeapExp& obj();

private:
    HeapExp mObj;
};

}  // namespace mem

#endif
