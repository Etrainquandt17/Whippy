#define MEM_EXPLICITAUTODELETEARRAY_INLINE
#include "mint/Heap.h"

#include "hel/common/ExplicitSingleton.h"
#include "hel/common/FixedString.h"
#include "mem/HeapUnit.h"
#include "mem/Memory.h"
#include "mintvm/MintSetting.h"
#include "std/cstring.h"
#include "std/tr1/reference_wrapper.h"
#include "xdata/XData.h"

// TODO: xdata/XData.h does not define these yet; this unit expands them.
namespace xdata {

inline bool XData::isValidData() const {
    return isValidEndian() && static_cast<const u32*>(mData)[2] >= 0x10;
}

inline const void* XData::dataHeadAddress() const {
    return isValidData() ? static_cast<const u8*>(mData) + 0x10 : 0;
}

}

namespace mint {

namespace {

Heap* t_heapPtr;
bool t_isAlreadyPrintWarn;

struct HeapParam {
    struct Unit {
        u32 name;
        u32 blockSize;
        u32 blockCount;
    };

    u32 count;
    Unit units[1];
};

void* t_MemoryAlloc(unsigned long size) {
    void* ptr = t_heapPtr->memAlloc(size);
    memset(ptr, 0, size);
    return ptr;
}

void t_MemoryFree(void* ptr) {
    t_heapPtr->memFree(ptr);
}

// TODO: the name and the place of this test are guesses; it is inlined into memFree.
bool t_IsInBlock(const mem::MemBlock& block, const void* ptr) {
    if (block.address() <= ptr && ptr < static_cast<const u8*>(block.address()) + block.size()) {
        return true;
    }
    return false;
}

}

Heap::Heap(mintvm::MintSetting& setting)
    : mParam("mint/Heap")
    , mMap()
    , mSetting(setting)
    , mHeap(hel::common::ExplicitSingleton<mem::Memory>::object_->sceneHeap(), 0x100000, "Mint")
    , mUnits(mHeap.obj()) {
    const HeapParam* param = static_cast<const HeapParam*>(mParam.xdata().dataHeadAddress());
    for (u32 i = 0; i < param->count; i++) {
        const HeapParam::Unit& unit = param->units[i];
        mUnits.add(hel::common::FixedStringIN<char, 32>::FromFormat("MNT%s", mParam.str(unit.name) + 4), std::tr1::ref(mHeap.obj()),
                   unit.blockSize, unit.blockCount, 4);
    }
    t_heapPtr = this;
    mSetting.setVMAllocator(t_MemoryAlloc, t_MemoryFree);
    mSetting.setRunAllocator(t_MemoryAlloc, t_MemoryFree);
}

// TODO: two registers. The original walks the map with the iterator in r4 and the parent it reads in r5; here
// they are the other way round.
Heap::~Heap() {
    for (Map::iterator it = mMap.begin(); it != mMap.end(); ++it) {
    }
    mSetting.setRunAllocator(0, 0);
    mSetting.setVMAllocator(0, 0);
    t_heapPtr = 0;
    mUnits.clear();
}

void* Heap::memAlloc(unsigned long size) {
    for (u32 i = 0; i < mUnits.count(); i++) {
        mem::HeapUnit& unit = mUnits[i];
        if (size <= unit.memBlockSize()) {
            if (unit.isFull()) {
                if (!t_isAlreadyPrintWarn) {
                    t_isAlreadyPrintWarn = true;
                }
                // TODO: mem::HeapExp is a mem::IAllocator; mem/HeapExp.h does not say so yet.
                return reinterpret_cast<mem::IAllocator&>(mHeap.obj()).allocatorAlloc(size, 4);
            }
            return unit.alloc(size);
        }
    }
    return mHeap.obj().alloc(size);
}

void Heap::memFree(void* ptr) {
    for (u32 i = 0; i < mUnits.count(); i++) {
        mem::HeapUnit& unit = mUnits[i];
        if (t_IsInBlock(unit.memBlock(), ptr)) {
            unit.free(ptr);
            return;
        }
    }
    mHeap.obj().free(ptr);
}

}
