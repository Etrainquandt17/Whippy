#include "scn/step/hero/wing/Wing.h"

#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/wing/StateDashAttack.h"
#include "scn/step/hero/wing/StateDiveAttack.h"
#include "scn/step/hero/wing/StateFlight.h"
#include "scn/step/hero/wing/StateShot.h"
#include "scn/step/hero/wing/StateUnderAttack.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

Wing::Wing(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Wing::~Wing() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x13);
    }
}

#define MF_FUNCTION setup__Q53scn4step4hero4wing4WingFv
void Wing::setup() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    Gear* gear;
    u32 i;
    u32 last;
    u32 limit;

    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/wing/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x13, motion);
    asm {
        bl      after1
        opword  MF_WORD(0x8C)
        opword  0x83562D76
    after1:
        mflr    r14
        lwz     r25, 0x0(r14)
        stw     r25, expected
    }
    hash = 0xB3;
    mHero.model().hat().set(modeldesc::Wing::HatPath(), modeldesc::Wing::HatModel());
    asm {
        bl      after2
        opword  0xD0542292
        opword  0x50D96B91
        opword  MF_WORD(0xD8)
        opword  0xC870F092
        opword  MF_WORD(0xE0)
        opword  0x796EE20C
    after2:
        mflr    r16
        lwz     r22, 0x8(r16)
        lwz     r24, 0x10(r16)
        stw     r24, start
        stw     r22, end
    }
    mHero.model().hat().addDynamics(modeldesc::Wing::HatDynaL());
    mHero.model().hat().addDynamics(modeldesc::Wing::HatDynaR());
    limit = end - start + 1;
    i = 1;
    last = end;
    gear = &mHero.model().hat();
    gear->setAnim(modeldesc::Wing::HatPath(), modeldesc::Wing::HatAnim());
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
    }
    mHero.model().hat().anim().start(0x18, false);
    if ((hash ^ expected) != 0) {
        volatile u32 response;
        volatile u32 mfBase;
        volatile u32 offset;
        volatile u32 key;

        asm {
            bl      after3
            opword  0x547E280A
            opword  0x48D40880
            opword  MF_WORD(0x1D8)
        after3:
            mflr    r26
            lwz     r19, 0x8(r26)
            stw     r19, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x1FC)
            opword  0xC4A85B92
            opword  0xD7F39206
            opword  MF_WORD(0x208)
        after4:
            mflr    r18
            lwz     r21, 0x0(r18)
            stw     r18, mfBase
            lwz     r20, 0xc(r18)
            stw     r21, offset
            stw     r20, key
        }
        response = offset + key;
        response = response + mfBase;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        mIsSetup = true;
    }
}
#undef MF_FUNCTION

bool Wing::tryToChangeStateOnInterval() {
    return StateFlight::TryToChangeState(&mHero);
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero4wing4WingFv
bool Wing::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xF45C4592
        opword  MF_WORD(0x34)
        opword  0xB0B09A80
    after1:
        mflr    r30
        lwz     r21, 0x0(r30)
        stw     r21, end
        lwz     r21, 0x8(r30)
        stw     r21, start
    }
    limit = end - start + 1;
    last = end;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000193;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x5FB6372B
    after2:
        mflr    r16
        lwz     r15, 0x0(r16)
        stw     r15, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected == 0 && mHero.water().isInWater()) {
        return false;
    }
    if (hash - expected == 0 && mHero.stateChecker().isFloat()) {
        return false;
    }
    if (hash - expected == 0 &&
        (StateFlight::TryToChangeState(&mHero) || StateDiveAttack::TryToChangeState(&mHero) || StateDashAttack::TryToChangeState(&mHero) ||
         StateUnderAttack::TryToChangeState(&mHero) || StateShot::TryToChangeState(&mHero))) {
        return true;
    }
    return expected != hash;
}
#undef MF_FUNCTION

}
}
}
}
