#include "scn/step/boss/lowper/BackEffectCtrl.h"

#include "metafortress.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

BackEffectCtrl::BackEffectCtrl(Boss& boss)
    : mBoss(boss)
    , mIsRequested(true)
    , mIsDead(false) {
}

BackEffectCtrl::~BackEffectCtrl() {}

void BackEffectCtrl::update() {
    if (mIsDead) {
        return;
    }
    if (mIsRequested) {
        if (mBoss.location().pos().z > 5.0f) {
            release();
        }
    } else {
        if (mBoss.location().pos().z < 10.0f) {
            request();
        }
    }
}

void BackEffectCtrl::request() {
    if (!mIsDead && !mIsRequested) {
        mIsRequested = true;
        mBoss.effect().back().requestN(static_cast<effect::Kind>(0x38A), 3);
    }
}

#define MF_FUNCTION release__Q53scn4step4boss6lowper14BackEffectCtrlFv
void BackEffectCtrl::release() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 tail;
    u32 i;
    u32 limit;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x90E4730F
        opword  MF_WORD(0x34)
        opword  0x90822280
    after1:
        mflr    r14
        lwz     r26, 0x0(r14)
        lwz     r17, 0x8(r14)
        add     r26, r26, r14
        add     r17, r17, r26
        stw     r26, start
        stw     r17, end
    }
    i = 1;
    tail = end;
    limit = tail - start + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(tail - 1 - i);
        hash *= 0x01000181;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x9C)
        opword  0xEC3C4836
    after2:
        mflr    r28
        lwz     r27, 0x0(r28)
        stw     r27, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || mIsRequested) {
        mIsRequested = expected != hash;
        mBoss.effect().back().release();
    }
}
#undef MF_FUNCTION

void BackEffectCtrl::onDead() {
    mBoss.effect().back().release();
    mIsRequested = false;
    mIsDead = true;
}

}
}
}
}
