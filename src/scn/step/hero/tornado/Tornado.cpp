#include "scn/step/hero/tornado/Tornado.h"
#include "g3d/ResFileRepository.h"
#include "gobj/FootState.h"
#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/tornado/StateAttack.h"
#include "scn/step/hero/tornado/StateGust.h"
#include "scn/step/hero/tornado/StateScrewTackle.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace tornado {

Tornado::Tornado(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false)
    , mIsHatWind(false)
    , mScrewTackleCount(0) {
}

Tornado::~Tornado() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0xE);
    }
}

void Tornado::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/tornado/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0xE, motion);
    mHero.model().hat().set(modeldesc::Tornado::HatPath(), modeldesc::Tornado::HatModel());
    mHero.model().hat().setAnim(modeldesc::Tornado::HatPath(), modeldesc::Tornado::HatAnim());
    mHero.model().hat().anim().start(0, true);
    requestHatWind();
    mIsSetup = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero7tornado7TornadoFv
bool Tornado::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0x811C9E53;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xB045FD80
        opword  0x80104A92
        opword  MF_WORD(0x38)
        opword  0xC4DC4080
        opword  0xE853E393
    after1:
        mflr    r24
        lwz     r23, 0x0(r24)
        add     r23, r23, r24
        stw     r23, start
        lwz     r19, 0xc(r24)
        add     r23, r23, r19
        stw     r23, end
    }
    base = start;
    limit = end - base;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0xAF6BE00E
    after2:
        mflr    r21
        lwz     r16, 0x0(r21)
        stw     r16, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash = (expected & ~hash) | (hash & ~expected);
    hash |= hash << 13;
    if (hash == 0) {
        if (mHero.water().isInWater()) {
            return false;
        }
        if (mHero.stateChecker().isFloat()) {
            return false;
        }
        if (StateGust::TryToChangeState(&mHero)) {
            return true;
        }
        if (StateScrewTackle::TryToChangeState(&mHero, mScrewTackleCount)) {
            mScrewTackleCount++;
            return true;
        }
        if (StateAttack::TryToChangeState(&mHero)) {
            endContinueScrewTackle();
            return true;
        }
        return false;
    } else {
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 response;
        volatile u32 base2;

        asm {
            bl      after3
            opword  0x2CF9E993
            opword  0xD84B8E80
            opword  MF_WORD(0x19C)
        after3:
            mflr    r28
            lwz     r29, 0x8(r28)
            stw     r29, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0x1C0)
            opword  MF_WORD(0x1C4)
        after4:
            mflr    r16
            stw     r16, base2
            lwz     r30, 0x0(r16)
            stw     r30, offset
            lwz     r20, 0x4(r16)
            stw     r20, addend
        }
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    }
}
#undef MF_FUNCTION

void Tornado::onShowHero() {
    requestHatWind();
}

void Tornado::onHideHero() {
    releaseHatWind();
}

#define MF_FUNCTION procAnim__Q53scn4step4hero7tornado7TornadoFv
void Tornado::procAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x7319AB2C
    after1:
        mflr    r29
        lwz     r24, 0x0(r29)
        stw     r24, expected
        bl      after2
        opword  0x504DC391
        opword  MF_WORD(0x48)
        opword  MF_WORD(0x4C)
    after2:
        mflr    r24
        lwz     r16, 0x8(r24)
        lwz     r17, 0x4(r24)
        add     r16, r17, r16
        stw     r16, end
        stw     r17, start
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
        i += 2;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash == expected) {
        if (!mIsSetup) {
            return;
        }
        if (!mHero.abilityManager().isStarted()) {
            return;
        }
        if (mHero.footState().isGround()) {
            endContinueScrewTackle();
        }
        if (!mHero.isVisible()) {
            return;
        }
        if (mHero.water().isInWater()) {
            releaseHatWind();
        } else {
            requestHatWind();
        }
    } else {
        volatile u32 subtrahend;
        volatile u32 response;
        volatile u32 base2;
        volatile u32 offset;

        asm {
            bl      after3
            opword  MF_WORD(0x158)
        after3:
            mflr    r19
            lwz     r14, 0x0(r19)
            stw     r14, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0x17C)
            opword  0x60CF3B90
            opword  MF_WORD(0x184)
        after4:
            mflr    r29
            lwz     r18, 0x0(r29)
            lwz     r17, 0x8(r29)
            stw     r17, subtrahend
            stw     r18, offset
            stw     r29, base2
        }
        response = offset - subtrahend;
        response = response + base2;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION endContinueScrewTackle__Q53scn4step4hero7tornado7TornadoFv
void Tornado::endContinueScrewTackle() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x71941D08
    after1:
        mflr    r30
        lwz     r15, 0x0(r30)
        stw     r15, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x5C2A1691
    after2:
        mflr    r16
        lwz     r17, 0x0(r16)
        stw     r17, start
        bl      after3
        opword  0xD8265A81
        opword  MF_WORD(0x58)
        opword  0x72DC540C
        opword  0x2C028993
    after3:
        mflr    r16
        lwz     r30, 0x4(r16)
        add     r30, r30, r17
        stw     r30, end
    }
    word = start;
    last = end;
    hash = 0;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 key;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 base;

        asm {
            bl      after4
            opword  0x38F01780
            opword  0xDC548780
            opword  MF_WORD(0xE4)
        after4:
            mflr    r14
            lwz     r30, 0x8(r14)
            stw     r30, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r30, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r30
            bl      after5
            opword  MF_WORD(0x108)
            opword  MF_WORD(0x10C)
        after5:
            mflr    r15
            lwz     r28, 0x0(r15)
            stw     r15, base
            lwz     r30, 0x4(r15)
            stw     r28, offset
            stw     r30, key
        }
        offset = offset ^ 0xA7;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        mScrewTackleCount = 0;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION requestHatWind__Q53scn4step4hero7tornado7TornadoFv
void Tornado::requestHatWind() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x483580B3
    after1:
        mflr    r24
        lwz     r17, 0x0(r24)
        stw     r17, expected
        bl      after2
        opword  0xBDD9EF0E
        opword  MF_WORD(0x40)
        opword  0xF4722C80
        opword  0x4C1A6F81
        opword  MF_WORD(0x4C)
        opword  0xB4032881
        opword  0x7CF3AD80
    after2:
        mflr    r18
        lwz     r15, 0x4(r18)
        stw     r15, start
        lwz     r30, 0x10(r18)
        add     r15, r15, r30
        stw     r15, end
    }
    hash = 0;
    limit = end - start + 1;
    i = 1;
    base = start;
    while (i != limit) {
        hash *= 151;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    if (hash == expected) {
        if (!mIsHatWind && mHero.model().hat().isValid()) {
            mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x545), 0);
            mIsHatWind = true;
        }
    } else {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 key;
        volatile u32 base2;

        asm {
            bl      after3
            opword  0x000B4B91
            opword  0x3CAF1A90
            opword  0xACED8080
            opword  MF_WORD(0x114)
        after3:
            mflr    r19
            lwz     r22, 0xc(r19)
            stw     r22, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x138)
            opword  0xB9993E0C
            opword  MF_WORD(0x140)
        after4:
            mflr    r30
            stw     r30, base2
            lwz     r26, 0x0(r30)
            stw     r26, offset
            lwz     r25, 0x8(r30)
            stw     r25, key
        }
        offset = offset ^ 0x2E;
        response = offset ^ key;
        response = response + base2;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    }
}
#undef MF_FUNCTION

void Tornado::releaseHatWind() {
    if (mIsHatWind && mHero.model().hat().isValid()) {
        mHero.model().hat().effect().release();
        mIsHatWind = false;
    }
}

}}}}  // namespace scn::step::hero::tornado
