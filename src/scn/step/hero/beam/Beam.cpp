#include "scn/step/hero/beam/Beam.h"
#include "dynamics/Desc.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/beam/StateBeamBlast.h"
#include "scn/step/hero/beam/StateBeamCharge.h"
#include "scn/step/hero/beam/StateBeamCycleBeam.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace beam {

Beam::Beam(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

Beam::~Beam() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(7);
    }
}

void Beam::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/beam/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(7, motion);
    mHero.model().hat().set(modeldesc::Beam::HatPath(), modeldesc::Beam::HatModel());
    mHero.model().hat().addDynamics(modeldesc::Beam::HatDynaL());
    mHero.model().hat().addDynamics(modeldesc::Beam::HatDynaR());
    mHero.model().weapon().set(modeldesc::Beam::StickPath(), modeldesc::Beam::StickModel());
    mHero.model().weapon().setAnim(modeldesc::Beam::StickPath(), modeldesc::Beam::StickAnim());
    mIsSetup = true;
}

bool Beam::tryToChangeState() {
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (mHero.water().isInWater()) {
        return false;
    }
    if (StateBeamBlast::TryToChangeState(&mHero) || StateBeamCycleBeam::TryToChangeState(&mHero)
        || StateBeamCharge::TryToChangeState(&mHero)) {
        mHero.effect()._1C0.release();
        return true;
    }
    return false;
}

void Beam::procAnim() {
    bool isVisible = true;
    if (mHero.water().isInWater() && !mHero.stateChecker().is_60()) {
        isVisible = false;
    }
    mHero.model().weapon().setVisibility(isVisible);
}

#define MF_FUNCTION onStateEndCleanUp__Q53scn4step4hero4beam4BeamFv
void Beam::onStateEndCleanUp() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 stop;
    u32 last;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x30895E80
    after1:
        mflr    r20
        lwz     r22, 0x0(r20)
        stw     r22, expected
    }
    hash = 0xC1;
    asm {
        bl      after2
        opword  0xF1AEEE00
        opword  0x403FF20D
        opword  MF_WORD(0x48)
        opword  0x30226381
        opword  MF_WORD(0x50)
        opword  0x389BE280
        opword  0xE8219E90
    after2:
        mflr    r14
        lwz     r23, 0x10(r14)
        stw     r23, start
        lwz     r15, 0x8(r14)
        stw     r15, end
    }
    last = start;
    limit = end;
    limit = limit - last;
    last = end;
    i = -1;
    last = last - 1;
    stop = limit - 1;
    while (i != stop) {
        i += 2;
        limit = hash << 4;
        hash = hash >> 28;
        hash = limit ^ hash;
        limit = last - i;
        limit = *(u16*)limit;
        hash ^= limit;
    }
    limit = hash << 3;
    hash += limit;
    limit = hash >> 11;
    hash ^= limit;
    limit = hash << 15;
    hash += limit;
    limit = expected;
    limit = hash - limit;
    if (limit != 0) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 base;

        asm {
            bl      after3
            opword  0xFCB95380
            opword  0x4CD96D81
            opword  MF_WORD(0xE8)
        after3:
            mflr    r27
            lwz     r19, 0x8(r27)
            stw     r19, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x10C)
            opword  0x609F7590
            opword  0xA8368480
            opword  MF_WORD(0x118)
        after4:
            mflr    r16
            stw     r16, base
            lwz     r17, 0x0(r16)
            stw     r17, offset
            lwz     r29, 0xc(r16)
            stw     r29, addend
        }
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else {
        if (mHero.model().weapon().isAnimExist()) {
            if (!mHero.wearBack().isBack()) {
                mHero.model().weapon().anim().clear();
            }
        }
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::hero::beam
