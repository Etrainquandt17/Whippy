#include "scn/step/hero/leaf/Leaf.h"

#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/leaf/StateBarrier.h"
#include "scn/step/hero/leaf/StateDance.h"
#include "scn/step/hero/leaf/StateDisorderShot.h"
#include "scn/step/hero/leaf/StateHide.h"
#include "scn/step/hero/leaf/StateShot.h"
#include "scn/step/hero/leaf/StateUpper.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace leaf {

Leaf::Leaf(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Leaf::~Leaf() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(3);
    }
}

void Leaf::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/leaf/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(3, motion);
    mHero.model().hat().set(modeldesc::Leaf::HatPath(), modeldesc::Leaf::HatModel());
    mHero.model().hat().addDynamics(modeldesc::Leaf::HatDynaL());
    mHero.model().hat().addDynamics(modeldesc::Leaf::HatDynaR());
    mIsSetup = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero4leaf4LeafFv
bool Leaf::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x96AD520E
        opword  0x2450DF92
        opword  MF_WORD(0x28)
        opword  0x631E8C0E
    after1:
        mflr    r28
        lwz     r21, 0xc(r28)
        lwz     r18, 0x0(r28)
        add     r18, r18, r28
        stw     r18, start
        add     r21, r21, r18
        stw     r21, end
    }
    hash = 0x811C9E29;
    word = start;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x60)
        opword  0xA596703D
    after2:
        mflr    r17
        lwz     r25, 0x0(r17)
        stw     r25, expected
    }
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001AB;
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
        (StateDisorderShot::TryToChangeState(&mHero) || StateUpper::TryToChangeState(&mHero) || StateDance::TryToChangeState(&mHero) ||
         StateShot::TryToChangeState(&mHero) || StateBarrier::TryToChangeState(&mHero) || StateHide::TryToChangeState(&mHero))) {
        return true;
    }
    return expected != hash;
}
#undef MF_FUNCTION

bool Leaf::tryToChangeStateOnInterval() {
    if (mHero.water().isInWater()) {
        return false;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (StateUpper::TryToChangeState(&mHero) || StateDance::TryToChangeState(&mHero) || StateBarrier::TryToChangeState(&mHero) ||
        StateHide::TryToChangeState(&mHero)) {
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::hero::leaf
