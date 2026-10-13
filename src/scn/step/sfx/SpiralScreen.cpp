#define REVOLUTION_GX_GXVERT_PLAIN_PARAMETERS

#include "scn/step/sfx/SpiralScreen.h"

#include "hel/math/Math.h"
#include "metafortress.h"
#include "revolution/gx/GXGeometry.h"
#include "revolution/gx/GXVert.h"
#include "scn/step/Component.h"
#include "scn/step/ostop/Manager.h"
#include "sfx/Manager.h"

namespace xdata {

inline bool XData::isValidData() const {
    return isValidEndian() && static_cast<const u32*>(mData)[2] >= 0x10;
}

inline const void* XData::dataHeadAddress() const {
    return isValidData() ? static_cast<const u8*>(mData) + 0x10 : 0;
}

}

namespace scn {
namespace step {
namespace sfx {

namespace {

// TODO: what the original has here is not known. For the outer ring the vector's address is taken ahead of the
// angle, which this compiler does for an inline function expanded once that converts the angle itself; for the
// inner ring hel::math::Math::DegToRad gives the original's order.
inline void t_rotateDeg(hel::math::Vector2& v, f32 deg) {
    v.rotate(0.017453292f * deg);
}

}

#define MF_FUNCTION __ct__Q43scn4step3sfx12SpiralScreenFRQ33scn4step9ComponentRQ23sfx7Manager
SpiralScreen::SpiralScreen(Component& component, ::sfx::Manager& manager)
    : mComponent(component)
    , mManager(manager)
    , mParam("step/sfx/SpiralScreen")
    , mIsAnim(false)
    , mFlag(static_cast<ostop::Flag>(0))
    , _20(0)
    , _24(4)
    , _28(0.04f)
    , _2C(0.004f)
    , mCenter(0.5f, 0.5f) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 addend;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x904E2D81
        opword  0x70A57F80
        opword  MF_WORD(0xAC)
        opword  0x04BD2493
        opword  0x10B70780
        opword  MF_WORD(0xB8)
        opword  0x807C0580
        opword  0x34E0D290
    after1:
        mflr    r15
        lwz     r25, 0x8(r15)
        lwz     r14, 0x14(r15)
        stw     r14, end
        stw     r25, start
    }
    hash = 0x811C9E53;
    asm {
        bl      after2
        opword  MF_WORD(0xE4)
        opword  0xA94AF359
    after2:
        mflr    r16
        lwz     r24, 0x0(r16)
        stw     r24, expected
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
    }
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0xBC012190
            opword  0x30FC6793
            opword  0x78186081
            opword  MF_WORD(0x158)
        after3:
            mflr    r29
            lwz     r16, 0xc(r29)
            stw     r16, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x17C)
            opword  0x78A9710B
            opword  MF_WORD(0x184)
        after4:
            mflr    r23
            lwz     r28, 0x0(r23)
            lwz     r18, 0x8(r23)
            stw     r18, addend
            stw     r28, offset
            stw     r23, mfBase
        }
        offset = offset - 0x1E;
        response = offset + addend;
        response = response + mfBase;
        asm {
            lwz     r24, response
            mtlr    r24
            blr
        }
    } else {
        if (param()._C == 12345678) {
            _24 = param()._0;
            _28 = param()._4;
            _2C = param()._8;
        }
    }
}
#undef MF_FUNCTION

SpiralScreen::~SpiralScreen() {}

void SpiralScreen::update() {
    static const f32 angle = 9.0f;

    if (mIsAnim && !mComponent.objStopManager().isStopped(mFlag)) {
        _20++;
        for (u32 n = 0; n < 20; n++) {
            if (_20 > n * _24) {
                _88[n] += _28;
                _38[n] += _88[n];
                if (n < 19) {
                    _D8[n] -= _2C;
                    if (_D8[n] < 0.0f) {
                        _D8[n] = 0.0f;
                    }
                }
            }
        }
        // A Vector2 built here would be a second use of the default constructor, which the original expands.
        hel::math::Vec2 center;
        center.x = 0.5f;
        center.y = 0.5f;
        for (u32 n = 0; n < 20; n++) {
            f32 rate;
            if (hel::math::Math::EqZero(_128[n])) {
                rate = 0.0f;
            } else {
                rate = _D8[n] / _128[n];
            }
            hel::math::Vector2 pos = hel::math::Math::LinearInterpolation(mCenter, reinterpret_cast<const hel::math::Vector2&>(center), rate);
            for (u32 m = 0; m < 40; m++) {
                hel::math::Vector2 outer(_128[n], 0.0f);
                t_rotateDeg(outer, angle * m);
                _1A78[n][m] = outer + pos;
                hel::math::Vector2 inner(_D8[n], 0.0f);
                inner.rotate(hel::math::Math::DegToRad(angle * m + _38[n]));
                _178[n][m] = inner + pos;
            }
        }
    }
}

void SpiralScreen::draw() const {
    static const f32 DEPTH = -0.5f;

    if (mIsAnim) {
        mManager.screenRemapDrawBegin(false);
        for (u32 n = 0; n < 19; n++) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 82);
            for (u32 m = 0; m < 40; m++) {
                GXPosition3f32(_178[n][m].x * 2.0f - 1.0f, -(_178[n][m].y * 2.0f - 1.0f), DEPTH);
                GXTexCoord2f32(_1A78[n][m].x, _1A78[n][m].y);
                GXPosition3f32(_178[n + 1][m].x * 2.0f - 1.0f, -(_178[n + 1][m].y * 2.0f - 1.0f), DEPTH);
                GXTexCoord2f32(_1A78[n + 1][m].x, _1A78[n + 1][m].y);
            }
            GXPosition3f32(_178[n][0].x * 2.0f - 1.0f, -(_178[n][0].y * 2.0f - 1.0f), DEPTH);
            GXTexCoord2f32(_1A78[n][0].x, _1A78[n][0].y);
            GXPosition3f32(_178[n + 1][0].x * 2.0f - 1.0f, -(_178[n + 1][0].y * 2.0f - 1.0f), DEPTH);
            GXTexCoord2f32(_1A78[n + 1][0].x, _1A78[n + 1][0].y);
        }
        mManager.screenRemapDrawEnd();
    }
}

#define MF_FUNCTION startAnim__Q43scn4step3sfx12SpiralScreenFQ43scn4step5ostop4Flag
void SpiralScreen::startAnim(ostop::Flag flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 subtrahend;
    volatile u32 mfBase;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  0xAC869F48
    after1:
        mflr    r17
        lwz     r23, 0x0(r17)
        stw     r23, expected
        bl      after2
        opword  MF_WORD(0x50)
        opword  0x485B0280
    after2:
        mflr    r21
        lwz     r27, 0x0(r21)
        add     r27, r27, r21
        stw     r27, start
        bl      after3
        opword  MF_WORD(0x6C)
    after3:
        mflr    r21
        lwz     r18, 0x0(r21)
        add     r27, r27, r18
        stw     r27, end
    }
    base = start;
    limit = end - base + 1;
    hash = 0x811C9E29;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001AB;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after4
            opword  0x7E17CA0D
            opword  MF_WORD(0xEC)
        after4:
            mflr    r23
            lwz     r30, 0x4(r23)
            stw     r30, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r30, -0x4(r1)
            stw     r23, -0x8(r1)
            mtlr    r30
            bl      after5
            opword  MF_WORD(0x110)
            opword  0xD8C0E592
            opword  0x18B20093
            opword  MF_WORD(0x11C)
        after5:
            mflr    r24
            lwz     r20, 0xc(r24)
            stw     r20, subtrahend
            lwz     r20, 0x0(r24)
            stw     r24, mfBase
            stw     r20, offset
        }
        response = offset - subtrahend;
        response = response + mfBase;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else {
        startAnim(flag, param()._0, param()._4, param()._8);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION startAnim__Q43scn4step3sfx12SpiralScreenFQ43scn4step5ostop4FlagUlff
void SpiralScreen::startAnim(ostop::Flag flag, u32 a, f32 b, f32 c) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 tail;
    u32 size;
    u32 i;

    hash = 0x811C9E29;
    for (u32 n = 0; n < 20; n++) {
        _D8[n] = 0.0425f * n;
        _128[n] = _D8[n];
        _38[n] = 0.0f;
        _88[n] = 0.0f;
    }
    asm {
        bl      after1
        opword  MF_WORD(0xF0)
        opword  0x7146941C
    after1:
        mflr    r18
        lwz     r23, 0x0(r18)
        stw     r23, expected
    }
    _20 = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x110)
        opword  MF_WORD(0x114)
        opword  0x7B2C5E00
        opword  0xECFFED92
    after2:
        mflr    r25
        lwz     r18, 0x0(r25)
        add     r18, r18, r25
        stw     r18, start
        lwz     r28, 0x4(r25)
        add     r18, r18, r28
        stw     r18, end
    }
    _24 = a;
    tail = end;
    size = tail - start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(tail - 1 - i);
        hash *= 0x010001AB;
    }
    _28 = b;
    _2C = c;
    hash ^= hash >> 10;
    hash ^= hash << 20;
    mIsAnim = expected == hash;
    mFlag = flag;
}
#undef MF_FUNCTION

void SpiralScreen::setCenter(const hel::math::Vector2& center) {
    mCenter = center;
}

const SpiralScreen::Param& SpiralScreen::param() const {
    return mParam.data<Param>();
}

}}}  // namespace scn::step::sfx
