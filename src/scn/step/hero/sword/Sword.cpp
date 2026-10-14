#include "scn/step/hero/sword/Sword.h"
#include "g3d/ResFileRepository.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/sword/StateSwordAirSpin.h"
#include "scn/step/hero/sword/StateSwordAttack.h"
#include "scn/step/hero/sword/StateSwordAttackFinish.h"
#include "scn/step/hero/sword/StateSwordChargeStart.h"
#include "scn/step/hero/sword/StateSwordChopping.h"
#include "scn/step/hero/sword/StateSwordFloatSpin.h"
#include "scn/step/hero/sword/StateSwordRaising.h"
#include "scn/step/hero/sword/StateSwordThrust.h"
#include "scn/step/hero/sword/StateSwordUnderThrustStart.h"
#include "scn/step/hero/sword/StateSwordWaterSpin.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace sword {

Sword::Sword(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false) {
}

#define MF_FUNCTION __dt__Q53scn4step4hero5sword5SwordFv
Sword::~Sword() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 limit;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x3C)
        opword  0x7C9D9BBD
    after1:
        mflr    r19
        lwz     r14, 0x0(r19)
        stw     r14, expected
    }
    hash = 0xB3;
    asm {
        bl      after2
        opword  0x70A27E80
        opword  0x1FCBC50F
        opword  MF_WORD(0x60)
        opword  0xE0252593
        opword  0x34097F80
    after2:
        mflr    r30
        lwz     r25, 0x8(r30)
        stw     r25, start
        bl      after3
        opword  0x2C6E2501
        opword  MF_WORD(0x80)
        opword  0x1827830E
    after3:
        mflr    r30
        lwz     r25, 0x4(r30)
        stw     r25, end
    }
    limit = end - start;
    last = end;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 base;
        volatile u32 addend;
        volatile u32 response;
        volatile u32 offset;

        asm {
            bl      after4
            opword  0x406A5380
            opword  0x68731980
            opword  MF_WORD(0x10C)
        after4:
            mflr    r17
            lwz     r16, 0x8(r17)
            stw     r16, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r16
            bl      after5
            opword  MF_WORD(0x130)
            opword  0x18361080
            opword  MF_WORD(0x138)
        after5:
            mflr    r19
            stw     r19, base
            lwz     r17, 0x0(r19)
            stw     r17, offset
            lwz     r27, 0x8(r19)
            stw     r27, addend
        }
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    } else {
        if (mIsSetup) {
            mHero.model().mAnim.unregisterResFile(1);
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setup__Q53scn4step4hero5sword5SwordFv
void Sword::setup() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x384CFB80
    after1:
        mflr    r30
        lwz     r27, 0x0(r30)
        lwz     r28, 0x4(r30)
        stw     r27, start
        add     r28, r27, r28
        stw     r28, end
    }
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/sword/Motion", true);
    motion.bind(base, false);
    word = start;
    last = end;
    mHero.model().mAnim.registerResFile(1, motion);
    hash = 0;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    mHero.model().hat().set(modeldesc::Sword::HatPath(), modeldesc::Sword::HatModel());
    hash += hash << 13;
    asm {
        bl      after2
        opword  MF_WORD(0x120)
        opword  0x06EAFD53
    after2:
        mflr    r17
        lwz     r22, 0x0(r17)
        stw     r22, expected
    }
    mHero.model().hat().addDynamics(modeldesc::Sword::HatDyna());
    hash ^= hash >> 7;
    hash += hash << 3;
    mHero.model().weapon().set(modeldesc::Sword::SwordPath(), modeldesc::Sword::SwordModel());
    hash ^= hash >> 17;
    mHero.model().weapon().setAnim(modeldesc::Sword::SwordPath(), modeldesc::Sword::SwordAnim());
    hash += hash << 5;
    hash = (expected & ~hash) | (hash & ~expected);
    hash += hash * 13;
    if (hash == 0) {
        mIsSetup = true;
    } else {
        volatile u32 addend;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 base;

        asm {
            bl      after3
            opword  MF_WORD(0x1F4)
        after3:
            mflr    r14
            lwz     r26, 0x0(r14)
            stw     r26, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x218)
            opword  0x01D9C806
            opword  MF_WORD(0x220)
        after4:
            mflr    r19
            lwz     r23, 0x8(r19)
            stw     r23, addend
            lwz     r23, 0x0(r19)
            stw     r19, base
            stw     r23, offset
        }
        offset = offset - 0xE;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    }
}
#undef MF_FUNCTION

bool Sword::tryToChangeState() {
    if (StateSwordWaterSpin::TryToChangeState(&mHero)) {
        return true;
    }
    if (mHero.water().isInWater()) {
        return false;
    }
    if (StateSwordFloatSpin::TryToChangeState(&mHero)) {
        return true;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (StateSwordRaising::TryToChangeState(&mHero) || StateSwordUnderThrustStart::TryToChangeState(&mHero)
        || StateSwordThrust::TryToChangeState(&mHero) || StateSwordChopping::TryToChangeState(&mHero)
        || StateSwordAirSpin::tryToChangeState(&mHero) || StateSwordAttackFinish::TryToChangeState(&mHero)
        || StateSwordAttack::tryToChangeState(&mHero) || StateSwordChargeStart::TryToChangeState(&mHero)) {
        return true;
    }
    return false;
}

void Sword::onStateEndCleanUp() {
    if (mHero.model().weapon().isAnimExist()) {
        if (!mHero.wearBack().isBack()) {
            mHero.model().weapon().anim().clear();
        }
    }
}

}}}}  // namespace scn::step::hero::sword
