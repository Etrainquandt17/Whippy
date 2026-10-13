#ifndef MEM_MEMBLOCK_H
#define MEM_MEMBLOCK_H

#include "types.h"

namespace mem {

class MemBlock {
public:
    static MemBlock EmptyBlock();

    MemBlock(void* address, u32 size);

    // TODO: the original's assignment is the implicit one: a unit that assigns once copies the two words in place
    // (file::FileLoader::loadIN). Partly written units match only with the call, so until they are complete a unit
    // that needs the implicit one defines MEM_MEMBLOCK_IMPLICIT_ASSIGNMENT ahead of its includes.
#ifndef MEM_MEMBLOCK_IMPLICIT_ASSIGNMENT
    MemBlock& operator=(const MemBlock& other);
#endif

    // TODO: address() is startAddress() under a name made up before the symbol was known.
    void* address() const { return mAddress; }
    void* startAddress() const { return mAddress; }
    void* endAddress() const;
    u32 size() const { return mSize; }

private:
    u32 mSize;
    void* mAddress;
};

}

#endif
