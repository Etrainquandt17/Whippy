#include "gfx/XFBManager.h"

#include "gfx/VISetting.h"
#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"
#include "revolution/vi.h"

using hel::common::ExplicitSingleton;

namespace gfx {

XFBManager::XFBManager(const VISetting& setting)
    : mTarget1(setting.fbSize(), 0x20, ExplicitSingleton<mem::Memory>::object_->mem2FixHeap())
    , mTarget2(setting.fbSize(), 0x20, ExplicitSingleton<mem::Memory>::object_->mem2FixHeap())
    , mIsDrawTarget1(false) {
    VISetNextFrameBuffer(drawTargetXFB());
    VIWaitForRetrace();
    changeDrawTargetXFB();
}

void* XFBManager::drawTargetXFB() {
    if (mIsDrawTarget1) {
        return mTarget1.block().startAddress();
    }
    return mTarget2.block().startAddress();
}

void XFBManager::changeDrawTargetXFB() {
    mIsDrawTarget1 = !mIsDrawTarget1;
}

void* XFBManager::target1() {
    return mTarget1.block().startAddress();
}

void* XFBManager::target2() {
    return mTarget2.block().startAddress();
}

}  // namespace gfx
