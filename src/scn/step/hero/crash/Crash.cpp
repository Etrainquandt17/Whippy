#include "scn/step/hero/crash/Crash.h"

#include "g3d/ResFileRepository.h"
#include "gobj/GearModel.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/crash/StateCharge.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

namespace scn {
namespace step {
namespace hero {
namespace crash {

Crash::Crash(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false)
    , mIsHatLight(false) {
}

Crash::~Crash() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x16);
    }
}

void Crash::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/crash/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x16, motion);
    mHero.model().hat().set(modeldesc::Crash::HatPath(), modeldesc::Crash::HatModel());
    requestHatLight();
    mIsSetup = true;
}

#define MF_FUNCTION tryToChangeState__Q53scn4step4hero5crash5CrashFv
bool Crash::tryToChangeState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;
    volatile u32 key;
    u32 hash;
    u32 t;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  0x75698308
        opword  0xBCC29B80
        opword  MF_WORD(0x2C)
    after1:
        mflr    r16
        lwz     r21, 0x8(r16)
        stw     r21, start
        bl      after2
        opword  0x60720B80
        opword  0x1833E493
        opword  MF_WORD(0x48)
        opword  0x2B00BC00
        opword  0x94DF7A92
    after2:
        mflr    r16
        lwz     r18, 0x8(r16)
        add     r18, r18, r21
        stw     r18, end
    }
    last = end;
    word = start;
    hash = 0;
    asm {
        bl      after3
        opword  MF_WORD(0x74)
        opword  0x6BD6B9CF
    after3:
        mflr    r24
        lwz     r17, 0x0(r24)
        stw     r17, expected
    }
    for (; word != last; word += 2) {
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    t = expected;
    t = hash - t;
    hash = __cntlzw(t);
    t = hash >> 5;
    hash = t << 10;
    hash = t | hash;
    if (hash == 0) {
        asm {
            bl      after4
            opword  0x90170781
            opword  MF_WORD(0x100)
        after4:
            mflr    r28
            lwz     r20, 0x4(r28)
            stw     r20, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r20
            bl      after5
            opword  MF_WORD(0x124)
            opword  0x6CD5D091
            opword  0x3531340C
            opword  MF_WORD(0x130)
        after5:
            mflr    r29
            lwz     r16, 0x0(r29)
            lwz     r17, 0xc(r29)
            stw     r17, key
            stw     r16, offset
            stw     r29, base
        }
        offset = offset + 0xE6;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    } else {
        if (mHero.water().isInWater()) {
            return false;
        }
        if (mHero.stateChecker().isFloat()) {
            return false;
        }
        if (StateCharge::TryToChangeState(&mHero)) {
            return true;
        }
        return false;
    }
}
#undef MF_FUNCTION

void Crash::onShowHero() {
    requestHatLight();
}

void Crash::onHideHero() {
    releaseHatLight();
}

#define MF_FUNCTION procAnim__Q53scn4step4hero5crash5CrashFv
void Crash::procAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 stop;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x40FC2531
    after1:
        mflr    r28
        lwz     r15, 0x0(r28)
        stw     r15, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  0x34AA6181
        opword  0x74CF6493
        opword  MF_WORD(0x40)
        opword  0x8C6FEF0F
        opword  0x8430D780
        opword  MF_WORD(0x4C)
        opword  0x4C0D6992
        opword  0xD07E3102
    after2:
        mflr    r20
        lwz     r17, 0x14(r20)
        stw     r17, end
        lwz     r21, 0x8(r20)
        stw     r21, start
    }
    stop = end;
    p = start;
    p -= 2;
    while (p != stop - 2) {
        p += 2;
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected == 0 && !mIsSetup) {
        return;
    }
    if (hash - expected == 0 && !mHero.abilityManager().isStarted()) {
        return;
    }
    if (hash - expected == 0 && mHero.isVisible()) {
        if (mHero.water().isInWater()) {
            releaseHatLight();
        } else {
            requestHatLight();
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION requestHatLight__Q53scn4step4hero5crash5CrashFv
void Crash::requestHatLight() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    u32 hash;
    u32 t;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x00915380
        opword  0x04C66F80
    after1:
        mflr    r30
        lwz     r29, 0x0(r30)
        stw     r29, start
        bl      after2
        opword  MF_WORD(0x40)
    after2:
        mflr    r30
        lwz     r29, 0x0(r30)
        stw     r29, end
    }
    last = end;
    word = start;
    asm {
        bl      after3
        opword  MF_WORD(0x5C)
        opword  0x836683A0
    after3:
        mflr    r29
        lwz     r23, 0x0(r29)
        stw     r23, expected
    }
    hash = 0xB5;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        t = *(u16*)word;
        hash = (hash << 4) ^ (hash >> 28);
        hash = t ^ hash;
    }
    if (hash != expected) {
        asm {
            bl      after4
            opword  MF_WORD(0xB0)
        after4:
            mflr    r25
            lwz     r26, 0x0(r25)
            stw     r26, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r26
            bl      after5
            opword  MF_WORD(0xD4)
            opword  0x3A09AF0D
            opword  0x71429D04
            opword  MF_WORD(0xE0)
        after5:
            mflr    r24
            lwz     r21, 0xc(r24)
            stw     r21, key
            lwz     r21, 0x0(r24)
            stw     r24, base
            stw     r21, offset
        }
        offset = offset ^ 0xD;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    } else {
        if (!mIsHatLight && mHero.model().hat().isValid()) {
            mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0xBF), 0);
            mIsHatLight = true;
        }
    }
}
#undef MF_FUNCTION

void Crash::releaseHatLight() {
    if (mIsHatLight && mHero.model().hat().isValid()) {
        mHero.model().hat().effect().release();
        mIsHatLight = false;
    }
}

}
}
}
}
