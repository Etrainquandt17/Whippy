#ifndef MEM_HEAPEXPARRAYUSER_H
#define MEM_HEAPEXPARRAYUSER_H

#include "types.h"

namespace mem {

class HeapExp;
class HeapExpArray;

class HeapExpArrayUser {
public:
    HeapExpArrayUser(HeapExpArray& array);
    ~HeapExpArrayUser();

    HeapExp& obj();

private:
    u8 _0[0x8];
};

}

#endif
