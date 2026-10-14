#include "scn/step/hero/parasol/Parasol.h"
#include "g3d/ResFileRepository.h"
#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/parasol/Barrier.h"
#include "scn/step/hero/parasol/StateParasolDive.h"
#include "scn/step/hero/parasol/StateParasolDrill.h"
#include "scn/step/hero/parasol/StateParasolParachute.h"
#include "scn/step/hero/parasol/StateParasolSwing.h"
#include "scn/step/hero/parasol/StateParasolUnder.h"
#include "scn/step/hero/parasol/StateParasolWaterDive.h"
#include "scn/step/hero/parasol/StateParasolWaterDrill.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace parasol {

Parasol::Parasol(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false)
    , mIsParachute(false)
    , mIsParachuteKeep(false) {
}

Parasol::~Parasol() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0xB);
    }
}

void Parasol::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/parasol/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0xB, motion);
    mHero.model().weapon().set(modeldesc::Parasol::ParasolPath(), modeldesc::Parasol::ParasolModel());
    mHero.model().weapon().setAnim(modeldesc::Parasol::ParasolPath(), modeldesc::Parasol::ParasolAnim());
    mHero.model().subAnimControl().setLiftUpRHand(true);
    Barrier::SetValid(mHero, true);
    mIsSetup = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero7parasol7ParasolFv
bool Parasol::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0xFF0ADA02
        opword  MF_WORD(0x28)
        opword  0x30C5F093
        opword  0xEC05F400
        opword  MF_WORD(0x34)
        opword  0x50CD6F81
        opword  0xBCF60C90
    after1:
        mflr    r25
        lwz     r14, 0x4(r25)
        stw     r14, start
        lwz     r14, 0x10(r25)
        stw     r14, end
    }
    hash = 0x811C9DDB;
    last = end;
    limit = last - start + 1;
    mIsParachute = false;
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
        opword  MF_WORD(0xA8)
        opword  0x66955701
    after2:
        mflr    r18
        lwz     r16, 0x0(r18)
        stw     r16, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash == 0) {
        if (StateParasolWaterDive::TryToChangeState(&mHero) || StateParasolWaterDrill::TryToChangeState(&mHero)) {
            return true;
        }
        if (mHero.water().isInWater()) {
            return false;
        }
        if (StateParasolWaterDrill::TryToChangeState(&mHero)) {
            return true;
        }
        if (mHero.stateChecker().isFloat()) {
            return false;
        }
        if (StateParasolUnder::TryToChangeState(&mHero) || StateParasolDive::TryToChangeState(&mHero)
            || StateParasolDrill::TryToChangeState(&mHero) || StateParasolSwing::TryToChangeState(&mHero)) {
            return true;
        }
        if (StateParasolParachute::TryToChangeState(&mHero)) {
            mIsParachute = true;
            mIsParachuteKeep = true;
            return true;
        }
        return false;
    } else {
        volatile u32 base;
        volatile u32 offset;
        volatile u32 response;
        volatile u32 key;

        asm {
            bl      after3
            opword  MF_WORD(0x1CC)
        after3:
            mflr    r30
            lwz     r23, 0x0(r30)
            stw     r23, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x1F0)
            opword  0x73E9EB0E
            opword  0xD1778105
            opword  MF_WORD(0x1FC)
        after4:
            mflr    r29
            lwz     r16, 0x0(r29)
            stw     r29, base
            lwz     r27, 0xc(r29)
            stw     r16, offset
            stw     r27, key
        }
        offset = offset - 0x2A;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    }
}
#undef MF_FUNCTION

void Parasol::procAnim() {
    if (mIsSetup) {
        Barrier::AddAttack(mHero, mIsParachute);
    }
}

void Parasol::onStateEndCleanUp() {
    if (mHero.model().weapon().isValid() && !mHero.wearBack().isBack()) {
        mHero.model().weapon().anim().start(6, false);
    }
    if (!mIsParachuteKeep) {
        mIsParachute = false;
    }
    mIsParachuteKeep = false;
}

}}}}  // namespace scn::step::hero::parasol
