#include "mem/HeapCompactionNode.h"

namespace mem {

MemBlock HeapCompactionNode::block() const {
    return MemBlock(mAddress, size());
}

u32 HeapCompactionNode::size() const {
    return mSize & 0x7FFFFFFF;
}

void HeapCompactionNode::setSize(u32 size) {
    mSize = (mSize & 0x80000000) | (size & 0x7FFFFFFF);
}

void HeapCompactionNode::setAddrAndSize(void* address, u32 size) {
    mAddress = address;
    setSize(size);
}

bool HeapCompactionNode::isFree() const {
    return (mSize & 0x80000000) != 0;
}

void HeapCompactionNode::setIsFree(bool isFree) {
    mSize = (mSize & 0x7FFFFFFF) | (isFree ? 0x80000000 : 0);
}

}
