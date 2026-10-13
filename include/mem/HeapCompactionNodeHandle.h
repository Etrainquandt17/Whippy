#ifndef MEM_HEAPCOMPACTIONNODEHANDLE_H
#define MEM_HEAPCOMPACTIONNODEHANDLE_H

#include "mem/MemBlock.h"

namespace mem {

class HeapCompactionNode;

class HeapCompactionNodeHandle {
public:
    HeapCompactionNodeHandle();
    HeapCompactionNodeHandle(HeapCompactionNode& node);

    bool isValid() const;
    HeapCompactionNode* node();
    MemBlock block() const;

private:
    HeapCompactionNode* mNode;
};

}  // namespace mem

#endif
