#include "scn/step/carryitem/BoundAlgorithm.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "metafortress.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/IndiviUtil.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/chara/WorldCage.h"

using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace carryitem {

BoundAlgorithm::BoundAlgorithm(CarryItem& carryItem, u32 boundSE)
    : mObj(carryItem)
    , mCount(0)
    , mIsBound(false)
    , mFloorSEInterval(0)
    , mWallSEInterval(0)
    , mRoofSEInterval(0)
    , mCageSEInterval(0)
    , mSpeedV(0.1f)
    , mReduceV(0.0f)
    , mRateH(1.0f)
    , mRateVRoof(1.0f)
    , mBoundSE(boundSE) {
    init();
}

#define MF_FUNCTION __ct__Q43scn4step9carryitem14BoundAlgorithmFRQ43scn4step9carryitem9CarryItem
BoundAlgorithm::BoundAlgorithm(CarryItem& carryItem) : mObj(carryItem), mCount(0), mIsBound(false), mFloorSEInterval(0), mWallSEInterval(0), mRoofSEInterval(0), mCageSEInterval(0), mSpeedV(0.1f), mReduceV(0.0f), mRateH(1.0f), mRateVRoof(1.0f), mBoundSE(0x124) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x74)
        opword  0xFA0351FD
    after1:
        mflr    r16
        lwz     r15, 0x0(r16)
        stw     r15, expected
        bl      after2
        opword  0x345A6281
        opword  0x90E15C08
        opword  MF_WORD(0x94)
        opword  0x409BD280
        opword  MF_WORD(0x9C)
    after2:
        mflr    r25
        lwz     r16, 0x10(r25)
        lwz     r18, 0x8(r25)
        stw     r18, start
        stw     r16, end
    }
    last = end;
    word = start;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash *= 193;
        hash += *(u16*)word;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash == 0) {
        init();
    } else {
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 response;
        volatile u32 base;

        asm {
            bl      after3
            opword  0x847A6993
            opword  0x1C99C392
            opword  0xC06F8580
            opword  MF_WORD(0x124)
        after3:
            mflr    r21
            lwz     r14, 0xc(r21)
            stw     r14, -0x4(r1)
            stw     r21, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r21, -0x8(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0x148)
            opword  0x48D61A81
            opword  0x58FC4990
            opword  MF_WORD(0x154)
        after4:
            mflr    r14
            lwz     r30, 0xc(r14)
            stw     r30, addend
            lwz     r30, 0x0(r14)
            stw     r14, base
            stw     r30, offset
        }
        offset = offset - 0xB1;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION init__Q43scn4step9carryitem14BoundAlgorithmFv
void BoundAlgorithm::init() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0xAB4055D9
    after1:
        mflr    r18
        lwz     r20, 0x0(r18)
        stw     r20, expected
        bl      after2
        opword  MF_WORD(0x40)
        opword  MF_WORD(0x44)
        opword  0xB246A601
    after2:
        mflr    r15
        lwz     r27, 0x0(r15)
        lwz     r23, 0x4(r15)
        add     r27, r27, r15
        add     r23, r23, r27
        stw     r27, start
        stw     r23, end
    }
    mObj.worldCage().setIsValid(true);
    last = end;
    word = start;
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
    hash = __cntlzw(hash - expected);
    hash = (hash >> 5) + ((hash >> 5) * 47);
    if (hash == 0) {
        volatile u32 response;
        volatile u32 base;
        volatile u32 subtrahend;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0x7C1A7A93
            opword  MF_WORD(0xF0)
        after3:
            mflr    r19
            lwz     r22, 0x4(r19)
            stw     r22, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x114)
            opword  0xBCF94292
            opword  MF_WORD(0x11C)
        after4:
            mflr    r16
            lwz     r27, 0x0(r16)
            stw     r16, base
            lwz     r28, 0x8(r16)
            stw     r27, offset
            stw     r28, subtrahend
        }
        offset = offset - 0x6C;
        response = offset - subtrahend;
        response = response + base;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        mObj.footState().setAir();
    }
}
#undef MF_FUNCTION

BoundAlgorithm::~BoundAlgorithm() {
    mObj.worldCage().setIsValid(false);
}

void BoundAlgorithm::procMove() {}

void BoundAlgorithm::procFixPos() {
    mIsBound = false;
    chara::MapCollResult result = mObj.mapColl().result();
    if (result.isHitFloor()) {
        mObj.move().setSpeedV(mSpeedV);
        obj().move().setSpeedH(mRateH * obj().move().velocity().x);
        if (mObj.move().velocity().y < 0.025f) {
            mObj.move().resetVelocity();
            mSpeedV = 0.0f;
        } else if (mFloorSEInterval == 0) {
            mObj.soundSE().start(mBoundSE);
            mFloorSEInterval = 5;
            mSpeedV -= mReduceV;
            mIsBound = true;
            mCount++;
        }
    } else if (mFloorSEInterval != 0) {
        mFloorSEInterval--;
    }
    if (result.isHitWall()) {
        obj().move().setSpeedH(-1.0f * obj().move().velocity().x);
        if (mWallSEInterval == 0) {
            mObj.soundSE().start(mBoundSE);
            mWallSEInterval = 5;
        }
    } else if (mWallSEInterval != 0) {
        mWallSEInterval--;
    }
    if (result.isHitRoof()) {
        obj().move().setSpeedV(-mRateVRoof * Math::Abs(obj().move().velocity().y));
        obj().move().setSpeedH(mRateH * obj().move().velocity().x);
        if (mRoofSEInterval == 0) {
            mObj.soundSE().start(mBoundSE);
            mRoofSEInterval = 5;
        }
    } else if (mRoofSEInterval != 0) {
        mRoofSEInterval--;
    }
    if (mObj.worldCage().isCorrected()) {
        Vector2 diff = mObj.worldCage().getCorrectedDiff();
        if (Math::Abs(diff.x) > 0.0001f) {
            int sign = diff.x < 0.0f ? -1 : 1;
            // TODO: the original multiplies in the other order (fmuls f31, f1, f0: the absolute value first).
            obj().move().setSpeedH(Math::Abs(obj().move().velocity().x) * static_cast<f32>(sign));
        }
        if (diff.y < -0.0001f) {
            obj().move().setSpeedV(-Math::Abs(obj().move().velocity().y));
            if (mCageSEInterval == 0) {
                mObj.soundSE().start(mBoundSE);
                mCageSEInterval = 5;
            }
        }
    } else if (mCageSEInterval != 0) {
        mCageSEInterval--;
    }
    if (IndiviUtil::IsDeadOnDamageField(mObj) && (mObj.mapColl().result()._6 || mObj.mapColl().result()._7)) {
        mObj.deadWithEffect();
    }
}

u32 BoundAlgorithm::getCount() {
    return mCount;
}

#define MF_FUNCTION setSpeedV__Q43scn4step9carryitem14BoundAlgorithmFf
void BoundAlgorithm::setSpeedV(f32 speed) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x6CB21592
        opword  MF_WORD(0x30)
        opword  0xCBFE6F06
        opword  MF_WORD(0x38)
    after1:
        mflr    r22
        lwz     r30, 0x4(r22)
        lwz     r15, 0xc(r22)
        add     r15, r30, r15
        stw     r30, start
        stw     r15, end
    }
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x2F827980
    after2:
        mflr    r28
        lwz     r26, 0x0(r28)
        stw     r26, expected
    }
    hash = 0x811C9DC5;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000181;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    if (hash == 0) {
        mSpeedV = speed;
    } else {
        volatile u32 response;
        volatile u32 base;
        volatile u32 key;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0x7CBD230B
            opword  0xD099FF80
            opword  MF_WORD(0xF0)
        after3:
            mflr    r24
            lwz     r29, 0x8(r24)
            stw     r29, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0x114)
            opword  0xDCF59B93
            opword  MF_WORD(0x11C)
        after4:
            mflr    r23
            lwz     r20, 0x8(r23)
            stw     r20, key
            lwz     r20, 0x0(r23)
            stw     r23, base
            stw     r20, offset
        }
        offset = offset + 0xAB;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setReduceV__Q43scn4step9carryitem14BoundAlgorithmFf
void BoundAlgorithm::setReduceV(f32 reduce) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xF0EE2F80
        opword  0x6C461190
    after1:
        mflr    r29
        lwz     r20, 0x0(r29)
        add     r20, r20, r29
        stw     r20, start
        bl      after2
        opword  MF_WORD(0x50)
    after2:
        mflr    r29
        lwz     r26, 0x0(r29)
        add     r20, r20, r26
        stw     r20, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xB0)
        opword  0xE207AA0B
    after3:
        mflr    r28
        lwz     r14, 0x0(r28)
        stw     r14, expected
    }
    if (hash == expected) {
        mReduceV = reduce;
    } else {
        volatile u32 response;
        volatile u32 addend;
        volatile u32 base;
        volatile u32 offset;

        asm {
            bl      after4
            opword  0x6CFD9E80
            opword  0x3CA11093
            opword  0x2338770F
            opword  MF_WORD(0xE8)
        after4:
            mflr    r20
            lwz     r27, 0xc(r20)
            stw     r27, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r20, -0x8(r1)
            mtlr    r27
            bl      after5
            opword  MF_WORD(0x10C)
            opword  0x740A2F81
            opword  MF_WORD(0x114)
        after5:
            mflr    r29
            lwz     r23, 0x0(r29)
            lwz     r14, 0x8(r29)
            stw     r14, addend
            stw     r23, offset
            stw     r29, base
        }
        offset = offset - 2;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setRateH__Q43scn4step9carryitem14BoundAlgorithmFf
void BoundAlgorithm::setRateH(f32 rate) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x983B2381
        opword  MF_WORD(0x34)
    after1:
        mflr    r15
        lwz     r28, 0x0(r15)
        lwz     r22, 0x8(r15)
        stw     r22, end
        stw     r28, start
    }
    last = end;
    word = start;
    asm {
        bl      after2
        opword  MF_WORD(0x58)
        opword  0xED4B79AD
    after2:
        mflr    r20
        lwz     r28, 0x0(r20)
        stw     r28, expected
    }
    hash = 0;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash *= 193;
        hash += *(u16*)word;
    }
    if (hash != expected) {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 subtrahend;
        volatile u32 base;

        asm {
            stw     r27, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xA4)
            opword  0xFCFF6081
            opword  0x2698B40F
            opword  0xF436FA93
        after3:
            mflr    r27
            lwz     r14, 0x0(r27)
            stw     r14, 0x0(r1)
            stw     r27, 0x4(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0xCC)
            opword  MF_WORD(0xD0)
        after4:
            mflr    r27
            lwz     r20, 0x0(r27)
            stw     r27, base
            lwz     r25, 0x4(r27)
            stw     r20, offset
            stw     r25, subtrahend
        }
        offset = offset + 0xCD;
        response = offset - subtrahend;
        response = response + base;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    } else {
        mRateH = rate;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setRateVRoof__Q43scn4step9carryitem14BoundAlgorithmFf
void BoundAlgorithm::setRateVRoof(f32 rate) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0xB47B9F80
        opword  0xD44F1F92
        opword  MF_WORD(0x34)
        opword  MF_WORD(0x38)
        opword  0x503F9A90
    after1:
        mflr    r28
        lwz     r20, 0xc(r28)
        stw     r20, start
        lwz     r19, 0x8(r28)
        stw     r19, end
    }
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x85E0759D
    after2:
        mflr    r30
        lwz     r14, 0x0(r30)
        stw     r14, expected
    }
    hash = 0x811C9DDB;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000193;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 offset;
        volatile u32 unused;
        volatile u32 response;
        volatile u32 base;

        asm {
            bl      after3
            opword  MF_WORD(0xD8)
        after3:
            mflr    r29
            addi    r30, r29, 0x10
            mtlr    r30
            lwz     r26, 0x0(r29)
            stw     r26, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r29, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x100)
            opword  0x80E87D07
            opword  0x38F05881
            opword  MF_WORD(0x10C)
        after4:
            mflr    r15
            stw     r15, base
            lwz     r29, 0x0(r15)
            stw     r29, offset
            lwz     r22, 0xc(r15)
            stw     r22, unused
        }
        offset = offset ^ 8;
        unused = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    } else {
        mRateVRoof = rate;
    }
}
#undef MF_FUNCTION

bool BoundAlgorithm::isBound() {
    return mIsBound;
}

void BoundAlgorithm::setIsBound(bool isBound) {
    mIsBound = isBound;
}

}}}  // namespace scn::step::carryitem
