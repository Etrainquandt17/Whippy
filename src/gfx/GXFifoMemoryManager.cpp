#include "gfx/GXFifoMemoryManager.h"

#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"
#include "revolution/os/OSCache.h"

using hel::common::ExplicitSingleton;

namespace gfx {

GXFifoMemoryManager::GXFifoMemoryManager(u32 size, u32 arg)
    : mSize(size)
    , _4(arg)
    , mData(ExplicitSingleton<mem::Memory>::object_->mem1FixHeap().allocatorAlloc(mSize + 0x400, 0x20))
    , mIsWriteEnable(true) {
    DCInvalidateRange(data(), mSize);
}

GXFifoMemoryManager::~GXFifoMemoryManager() {
    ExplicitSingleton<mem::Memory>::object_->mem1FixHeap().free(mData);
    mData = 0;
}

void* GXFifoMemoryManager::data() {
    return reinterpret_cast<void*>((reinterpret_cast<u32>(mData) + 0x3FF) & ~0x3FF);
}

void GXFifoMemoryManager::setWriteEnable() {
    mIsWriteEnable = true;
}

void GXFifoMemoryManager::setWriteDisable() {
    mIsWriteEnable = false;
}

bool GXFifoMemoryManager::isWriteEnable() const {
    return mIsWriteEnable;
}

}  // namespace gfx
