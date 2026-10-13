#include "mem/HeapCompactionNodeHandle.h"

#include "mem/HeapCompactionNode.h"

namespace mem {

HeapCompactionNodeHandle::HeapCompactionNodeHandle()
    : mNode(0) {}

HeapCompactionNodeHandle::HeapCompactionNodeHandle(HeapCompactionNode& node)
    : mNode(&node) {}

bool HeapCompactionNodeHandle::isValid() const {
    return mNode != 0;
}

HeapCompactionNode* HeapCompactionNodeHandle::node() {
    return mNode;
}

MemBlock HeapCompactionNodeHandle::block() const {
    return mNode->block();
}

}
