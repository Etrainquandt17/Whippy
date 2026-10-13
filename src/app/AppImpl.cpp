// The auto_ptr calls in this unit are only left out of line without -ipa file.
#pragma ipa function

#include "app/AppImpl.h"

#include "app/System.h"
#include "gfx/GXFifoMemoryManager.h"
#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapCompaction.h"
#include "mem/Memory.h"
#include "metafortress.h"
#include "seq/SequenceRoot.h"
#include "snd/SoundSystem.h"

// TODO: these are hid::HIDManager::updateMaster() and updateDebug(); declare
// them in hid/HIDManager.h and call them as members.
extern "C" {
void updateMaster__Q23hid10HIDManagerFv(hid::HIDManager* self);
void updateDebug__Q23hid10HIDManagerFv(hid::HIDManager* self);
}

namespace app {

#define MF_FUNCTION run__Q23app7AppImplFb
void AppImpl::run(bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  0xF4621C80
        opword  0x5C282581
        opword  MF_WORD(0x28)
    after1:
        mflr    r30
        lwz     r25, 0x8(r30)
        stw     r25, start
        bl      after2
        opword  0x14FC7492
        opword  0xECAC7993
        opword  MF_WORD(0x44)
        opword  0xD57D1F09
        opword  0xD401E791
    after2:
        mflr    r30
        lwz     r17, 0x8(r30)
        add     r17, r17, r25
        stw     r17, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 107;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash += hash << 13;
    updateMaster__Q23hid10HIDManagerFv(&mHidManager);
    asm {
        bl      after3
        opword  MF_WORD(0xAC)
        opword  0x3B62A99E
    after3:
        mflr    r18
        lwz     r21, 0x0(r18)
        stw     r21, expected
    }
    hash ^= hash >> 7;
    updateDebug__Q23hid10HIDManagerFv(&mHidManager);
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
    mSystem.gxFifoMemoryManager().setWriteDisable();
    for (;;) {
        std::auto_ptr<seq::ISequence> root;
        root.reset(new seq::SequenceRoot());
        runWithRootSequence(root);
        mFileManager.clearFiles();
        mPreLoadManager.waitToFinishLoading();
        mPreLoadManager.reset();
        hel::common::ExplicitSingleton<mem::Memory>::object_->externalHeap().compaction();
        mReset.onSoftReset();
        mHomeButtonMenu.onSoftReset();
        snd::onSoftReset();
        mStorageManager.onSoftReset();
    }
}
#undef MF_FUNCTION

}  // namespace app
