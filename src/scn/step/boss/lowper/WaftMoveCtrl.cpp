#include "scn/step/boss/lowper/WaftMoveCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/chara/Location.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

WaftMoveCtrl::WaftMoveCtrl(Boss& boss)
    : mBoss(boss), mCenter(boss.location().pos()), mPhaseX(0.0f), mPhaseY(0.0f), mMoveIntpRate(0.0f), mWaveWidth(0.0f),
      mWaveWidthTarget(0.0f), mIsValid(true) {}

WaftMoveCtrl::~WaftMoveCtrl() {}

void WaftMoveCtrl::update() {
    if (mIsValid) {
        const Param& param = mBoss.param().lowper();
        mWaveWidth = Math::Interpolate(mWaveWidth, mWaveWidthTarget, param._8C);
        mPhaseX += param._80;
        mPhaseY += param._84;
        if (mPhaseX >= 360.0f) {
            mPhaseX -= 360.0f;
        }
        if (mPhaseY >= 360.0f) {
            mPhaseY -= 360.0f;
        }
        Vector3 offset;
        offset.x = Math::SinDegF(mPhaseX);
        offset.y = Math::SinDegF(mPhaseY);
        offset *= mWaveWidth;
        offset.y *= param._88;
        offset += mCenter;
        Vector3 pos = Math::LinearInterpolation(mBoss.location().pos(), offset, mMoveIntpRate);
        mBoss.location().setPos(pos);
    }
}

void WaftMoveCtrl::setCenter(const Vector3& center) {
    mCenter = center;
}

void WaftMoveCtrl::setIsValid(bool isValid) {
    mIsValid = isValid;
}

void WaftMoveCtrl::setMoveIntpRate(f32 rate) {
    mMoveIntpRate = rate;
}

void WaftMoveCtrl::setWaveWidth(f32 width) {
    mWaveWidthTarget = width;
}

#define MF_FUNCTION getCenter__Q53scn4step4boss6lowper12WaftMoveCtrlCFv
Vector3 WaftMoveCtrl::getCenter() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x783D6C80
        opword  0xF4FC7193
        opword  MF_WORD(0x34)
        opword  0x6E56520F
        opword  0xD0F1B290
    after1:
        mflr    r20
        lwz     r23, 0x0(r20)
        lwz     r26, 0xc(r20)
        stw     r26, start
        stw     r23, end
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x6C)
        opword  0x05A18E9E
    after2:
        mflr    r27
        lwz     r21, 0x0(r27)
        stw     r21, expected
    }
    hash = 0x811C9E53;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001D1;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if ((hash ^ expected) != 0) {
        volatile u32 offset;
        volatile u32 key;
        volatile u32 response;
        volatile u32 base;

        asm {
            stw     r15, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xE4)
            opword  0xEE79E60F
            opword  0x84AC1681
            opword  0x94534B90
        after3:
            mflr    r15
            lwz     r27, 0x0(r15)
            stw     r27, 0x0(r1)
            stw     r15, 0x4(r1)
            mtlr    r27
            bl      after4
            opword  MF_WORD(0x10C)
            opword  0x4B142B0E
            opword  0x30E0D780
            opword  MF_WORD(0x118)
        after4:
            mflr    r30
            lwz     r22, 0x0(r30)
            stw     r30, base
            lwz     r27, 0xc(r30)
            stw     r22, offset
            stw     r27, key
        }
        offset = offset ^ 0xBD;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        return mCenter;
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::boss::lowper
