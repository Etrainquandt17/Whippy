#include "mem/HeapExp.h"

#include "mem/HeapMapUserRepos.h"
#include "mem/Utility.h"
#include "nrel/mem/ExpHeapAccessor.h"
#include "std/tr1/reference_wrapper.h"

namespace mem {

HeapExp::HeapExp(const hel::common::FixedString<32>& name, const MemBlock& block, bool noHeapMap, bool noFill)
    : mName(name)
    , mBlock(block)
    , mUsingBlockCount(0)
    , mNoFill(noFill)
    , mHeap(MEMCreateExpHeapEx(block.startAddress(), block.size(), 0)) {
    mTailAllocator.construct(std::tr1::ref(*this));
    if (!noHeapMap) {
        mMapUser.construct(std::tr1::ref(mHeap), static_cast<const char*>(mName));
        HeapMapUserRepos::Register(*mMapUser);
    }
}

HeapExp::~HeapExp() {
    if (mMapUser.isConstruct()) {
        HeapMapUserRepos::Unregister(*mMapUser);
        mMapUser.destruct();
    }
    mTailAllocator.destruct();
    MEMDestroyExpHeap(mHeap);
}

void* HeapExp::alloc(unsigned long size) {
    return alloc(size, 4);
}

void* HeapExp::alloc(unsigned long size, long align) {
    return alloc(size, align, false);
}

void* HeapExp::alloc(unsigned long size, long align, bool fromTail) {
    void* address = MEMAllocFromExpHeapEx(mHeap, size, align * (fromTail ? -1 : 1));
    if (!mNoFill) {
        Utility::MemSetU32(MemBlock(address, size), 0x7FBFFFFF);
    }
    mUsingBlockCount++;
    return address;
}

void HeapExp::free(void* address) {
    mUsingBlockCount--;
    MEMFreeToExpHeap(mHeap, address);
}

void* HeapExp::allocatorAlloc(u32 size, s32 align) {
    return alloc(size, align);
}

void HeapExp::allocatorFree(void* ptr) {
    free(ptr);
}

const char* HeapExp::heapName() const {
    return mName;
}

MemBlock HeapExp::heapMemBlock() const {
    return mBlock;
}

s32 HeapExp::heapUsingBlockCount() const {
    return mUsingBlockCount;
}

void HeapExp::heapDump() const {
    nrel::mem::ExpHeapAccessor accessor(mHeap);
    accessor.dump(nrel::mem::ExpHeapAccessor::DUMP_STYLE_0);
}

HeapExp::AllocFromTailAllocator::AllocFromTailAllocator(HeapExp& heap) : mHeap(heap) {}

void* HeapExp::AllocFromTailAllocator::allocatorAlloc(u32 size, s32 align) {
    return mHeap.alloc(size, align, true);
}

void HeapExp::AllocFromTailAllocator::allocatorFree(void* ptr) {
    mHeap.free(ptr);
}

IAllocator& HeapExp::allocFromTailAllocator() {
    return *mTailAllocator;
}

}  // namespace mem
