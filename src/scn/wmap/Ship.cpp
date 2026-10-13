#include "scn/wmap/Ship.h"

#include "g3d/CharaModelContext.h"
#include "g3d/ModelBufferOption.h"
#include "g3d/ModelContext.h"
#include "g3d/ResFileRepository.h"
#include "g3d/ResModelContext.h"
#include "mem/AutoHeapExp.h"
#include "mem/IAllocator.h"
#include "metafortress.h"
#include "scn/wmap/Component.h"
#include "scn/wmap/UnlockManager.h"

namespace scn {
namespace wmap {

namespace {

const char* UNLOCKED_ACTION_NAME_TABLE[] = {
    "Parts0", "Parts0", "Parts1", "Parts2", "Parts3", "Parts4", "Wait", "Wait",
};

}

#define MF_FUNCTION __ct__Q33scn4wmap4ShipFRQ33scn4wmap9Component
// TODO: mem::HeapExp is a mem::IAllocator; its header does not say so yet.
Ship::Ship(Component& component)
    : mComponent(component)
    , mResFile(component.resFileRepos().get("wmap/chara/Roah", false))
    , mModel(g3d::ModelContext(g3d::ResModelContext(mResFile, "TopL"), g3d::CharaModelContext::DefaultModelBufferOption(), 0,
                               g3d::CharaModelContext::DefaultNumView(), reinterpret_cast<mem::IAllocator&>(component.heap().obj()), false))
    , mUnlockKind(UNLOCK_KIND_0) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0xAC)
        opword  0x7C0802A8
    after1:
        mflr    r27
        lwz     r14, 0x0(r27)
        stw     r14, expected
    }
    mUnlockKind = mComponent.unlockManager().getAfterDemoUnlockKind();
    asm {
        bl      after2
        opword  0xCA916001
        opword  MF_WORD(0xE0)
        opword  MF_WORD(0xE4)
        opword  0x3B182608
        opword  0x44257C93
    after2:
        mflr    r22
        lwz     r21, 0x8(r22)
        lwz     r15, 0x4(r22)
        add     r21, r15, r21
        stw     r21, end
        stw     r15, start
    }
    hash = 0x811C9DC5;
    mModel.setAnim(mResFile, UNLOCKED_ACTION_NAME_TABLE[mUnlockKind]);
    i = 1;
    last = end;
    limit = last - start + 1;
    last -= 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000181;
        i += 2;
    }
    mModel.start(expected == hash);
}
#undef MF_FUNCTION

}
}
