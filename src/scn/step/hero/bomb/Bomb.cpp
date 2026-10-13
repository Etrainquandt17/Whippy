#include "scn/step/hero/bomb/Bomb.h"

#include "g3d/ResFileRepository.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/bomb/StateCharge.h"
#include "scn/step/hero/bomb/StatePut.h"
#include "scn/step/hero/bomb/StateSearchEnemy.h"
#include "scn/step/hero/bomb/StateSwing.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

Bomb::Bomb(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , _C(false)
    , mGearBombController(hero)
    , _40(0.0f)
    , _44(0) {
}

Bomb::~Bomb() {
    if (_C) {
        mHero.model().mAnim.unregisterResFile(0xF);
        mHero.soundSE()._330.stop();
        mHero.carryItemUser().setIsValid(true);
    }
}

void Bomb::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/bomb/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0xF, motion);
    mHero.model().hat().set(modeldesc::Bomb::HatPath(), modeldesc::Bomb::HatModel());
    mHero.model().hat().addDynamics(modeldesc::Bomb::HatDyna());
    mHero.model().body().set(modeldesc::Bomb::GuidePath(), modeldesc::Bomb::GuideModel());
    mHero.model().body().setAnim(modeldesc::Bomb::GuidePath(), modeldesc::Bomb::GuideAnim());
    mHero.model().body().anim().start(0, true);
    mHero.model().body().setVisibility(false);
    _C = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero4bomb4BombFv
bool Bomb::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 offset;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xC4FDC94C
    after1:
        mflr    r29
        lwz     r24, 0x0(r29)
        stw     r24, expected
        bl      after2
        opword  MF_WORD(0x44)
        opword  MF_WORD(0x48)
        opword  0x80686A81
    after2:
        mflr    r22
        lwz     r21, 0x0(r22)
        lwz     r23, 0x4(r22)
        add     r21, r21, r22
        add     r23, r23, r21
        stw     r21, start
        stw     r23, end
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000193;
        i += 2;
    }
    if ((hash ^ expected) == 0) {
        if (mHero.water().isInWater()) {
            return false;
        }
        if (mHero.stateChecker().isFloat()) {
            return false;
        }
        if (StatePut::TryToChangeState(&mHero, mGearBombController)
            || StateCharge::TryToChangeState(&mHero, mGearBombController)
            || StateSearchEnemy::TryToChangeState(&mHero, mGearBombController)) {
            return true;
        }
        if (mGearBombController.isHave() && StateSwing::TryToChangeState(&mHero, mGearBombController)) {
            return true;
        }
        return false;
    }
    asm {
        bl      after3
        opword  MF_WORD(0x174)
        opword  0xBC7E0C81
        opword  0x542AFD80
    after3:
        mflr    r30
        addi    r16, r30, 0x18
        mtlr    r16
        lwz     r14, 0x0(r30)
        stw     r14, -0x4(r1)
        stw     r16, 0x0(r1)
        stw     r30, 0x4(r1)
        blrl
        bl      after4
        opword  MF_WORD(0x1A4)
        opword  0x0820C391
        opword  MF_WORD(0x1AC)
    after4:
        mflr    r23
        stw     r23, mfBase
        lwz     r18, 0x0(r23)
        stw     r18, offset
        lwz     r25, 0x8(r23)
        stw     r25, addend
    }
    offset = offset - 0x70;
    response = offset + addend;
    response = response + mfBase;
    asm {
        lwz     r15, response
        mtlr    r15
        blr
    }
}
#undef MF_FUNCTION

void Bomb::procAnim() {
    if (_C) {
        mGearBombController.update();
        if (!mGearBombController.isHave() && mHero.model().mSubAnimControl.isLiftUpRHand()) {
            mHero.model().mSubAnimControl.setLiftUpRHand(false);
        }
    }
}

#define MF_FUNCTION onStateEndCleanUp__Q53scn4step4hero4bomb4BombFv
void Bomb::onStateEndCleanUp() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 stop;
    u32 p;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0xF1C60F83
    after1:
        mflr    r16
        lwz     r29, 0x0(r16)
        stw     r29, expected
        bl      after2
        opword  MF_WORD(0x34)
        opword  0x8C8C8880
        opword  0x38924B90
        opword  MF_WORD(0x40)
    after2:
        mflr    r27
        lwz     r26, 0x0(r27)
        stw     r26, end
        lwz     r26, 0xc(r27)
        stw     r26, start
    }
    p = start;
    stop = end;
    hash = 0x811C9E07;
    p -= 2;
    while (p != stop - 2) {
        p += 2;
        hash ^= *(u16*)p;
        hash *= 0x010001A7;
    }
    if (hash - expected == 0) {
        if (!_C) {
            asm {
                b       done
            }
        }
        if (hash - expected != 0 || (mGearBombController.isHave() && !mHero.stateChecker().isBombDanger())) {
            mHero.model().mSubAnimControl.setLiftUpRHand(true);
        }
        if (hash - expected != 0 || mHero.model()._1668.isValid()) {
            mHero.model()._1668.setVisibility(false);
        }
    }
done:;
}
#undef MF_FUNCTION

void Bomb::onGetEventItem() {
    clearBombIfHave();
}

void Bomb::onGimmickReactChangeState() {
    dropBombIfHave();
}

void Bomb::onStartClearDanceExternal() {
    clearBombIfHave();
}

void Bomb::onEnterWarpLowper() {
    clearBombIfHave();
}

void Bomb::onShowHero() {
    mGearBombController.onShowHero();
}

void Bomb::onHideHero() {
    mGearBombController.onHideHero();
}

void Bomb::onDead() {
    clearBombIfHave();
}

void Bomb::onCaptured() {
    clearBombIfHave();
}

void Bomb::onVacuumed() {
    clearBombIfHave();
}

void Bomb::onStartDemo() {
    clearBombIfHave();
}

void Bomb::onEnterDoor() {
    clearBombIfHave();
}

void Bomb::dropBombIfHave() {
    if (mGearBombController.isHave()) {
        mGearBombController.dropBomb();
    }
}

void Bomb::clearBombIfHave() {
    if (mGearBombController.isHave()) {
        mGearBombController.clearBomb();
    }
}

}
}
}
}
