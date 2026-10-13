#include "scn/step/hero/hammer/Hammer.h"

#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/hammer/StateAirSpin.h"
#include "scn/step/hero/hammer/StateFloatSpin.h"
#include "scn/step/hero/hammer/StateHammerCharge.h"
#include "scn/step/hero/hammer/StateSpin.h"
#include "scn/step/hero/hammer/StateStrongAirSpin.h"
#include "scn/step/hero/hammer/StateStrongSwing.h"
#include "scn/step/hero/hammer/StateUnderAttack.h"
#include "scn/step/hero/hammer/StateWaterSpin.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

Hammer::Hammer(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Hammer::~Hammer() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x11);
    }
}

void Hammer::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/hammer/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x11, motion);
    mHero.model().hat().set(modeldesc::Hammer::HatPath());
    mHero.model().weapon().set(modeldesc::Hammer::HammerPath(), modeldesc::Hammer::HammerModel());
    mHero.model().weapon().setAnim(modeldesc::Hammer::HammerPath(), modeldesc::Hammer::HammerAnim());
    mHero.model().mSubAnimControl.setLiftUpRHand(true);
    mIsSetup = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero6hammer6HammerFv
bool Hammer::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x8F5B2CBB
    after1:
        mflr    r25
        lwz     r23, 0x0(r25)
        stw     r23, expected
        bl      after2
        opword  MF_WORD(0x34)
        opword  0xC4276481
        opword  MF_WORD(0x3C)
    after2:
        mflr    r26
        lwz     r30, 0x0(r26)
        add     r30, r30, r26
        lwz     r17, 0x8(r26)
        stw     r30, start
        add     r17, r17, r30
        stw     r17, end
    }
    hash = 0;
    i = 1;
    base = start;
    limit = end - base + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0 && StateWaterSpin::TryToChangeState(&mHero)) {
        return true;
    }
    if (hash - expected == 0 && mHero.water().isInWater()) {
        return false;
    }
    if (hash - expected == 0 && StateFloatSpin::TryToChangeState(&mHero)) {
        return true;
    }
    if (hash - expected == 0 && mHero.stateChecker().isFloat()) {
        return false;
    }
    if (hash - expected == 0 &&
        (StateUnderAttack::TryToChangeState(&mHero) || StateStrongAirSpin::TryToChangeState(&mHero) || StateAirSpin::TryToChangeState(&mHero) ||
         StateSpin::TryToChangeStateSpin(&mHero) || StateStrongSwing::TryToChangeState(&mHero) || StateHammerCharge::TryToChangeState(&mHero))) {
        return true;
    }
    return expected != hash;
}
#undef MF_FUNCTION

#define MF_FUNCTION onStateEndCleanUp__Q53scn4step4hero6hammer6HammerFv
void Hammer::onStateEndCleanUp() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x881A3691
    after1:
        mflr    r30
        lwz     r14, 0x0(r30)
        add     r14, r14, r30
        stw     r14, start
        lwz     r16, 0x4(r30)
        add     r14, r14, r16
        stw     r14, end
    }
    hash = 0x811C9E53;
    i = 1;
    last = end;
    limit = last - start + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001D1;
        i += 2;
    }
    hash ^= hash >> 10;
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0x19290BFE
    after2:
        mflr    r26
        lwz     r16, 0x0(r26)
        stw     r16, expected
    }
    hash ^= hash << 20;
    if (hash - expected == 0 && mHero.model()._CF0.isAnimExist() && !mHero.wearBack().isBack()) {
        mHero.model()._CF0.anim().clear();
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::hero::hammer
