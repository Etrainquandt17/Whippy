#ifndef MEM_UTILITY_H
#define MEM_UTILITY_H

#include "mem/MemBlock.h"
#include "types.h"

namespace mem {

// TODO: the other functions.
class Utility {
public:
    static void MemSetU32(const MemBlock& block, u32 value);
};

}

#endif
