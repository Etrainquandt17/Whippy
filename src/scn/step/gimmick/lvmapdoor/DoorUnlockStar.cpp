#include "scn/step/gimmick/lvmapdoor/DoorUnlockStar.h"

#include "g3d/ModelAccessor.h"
#include "g3d/NodeAccessor.h"
#include "hel/common/Color.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraAccessor.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/core/BGMController.h"
#include "scn/step/sfx/BGFade.h"

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

#define MF_FUNCTION __ct__Q53scn4step7gimmick9lvmapdoor14DoorUnlockStarFRQ33scn4step9Component
DoorUnlockStar::DoorUnlockStar(Component& component)
    : mComponent(component)
    , mFrom()
    , mTo()
    , mPos()
    , _28(false)
    , mIsBoss(false)
    , mDoorPos()
    , mModel(component, "step/gimmick/Starlvmap", "TopL", true, false)
    , mEffect(component)
    , mZoomHandle(0)
    , mCounter()
    , mSE()
    , mState(STATE_NONE) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x9C)
        opword  0x49B42C0D
    after1:
        mflr    r29
        lwz     r23, 0x0(r29)
        stw     r23, expected
        bl      after2
        opword  MF_WORD(0xB4)
        opword  MF_WORD(0xB8)
    after2:
        mflr    r26
        lwz     r20, 0x0(r26)
        lwz     r24, 0x4(r26)
        stw     r24, start
        stw     r20, end
    }
    hash = 0;
    last = end;
    word = start;
    mEffect.changeLayer(core::DRAW_LAYER_KIND_4);
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash == 0) {
        mModel.setVisibility(false);
    } else {
        volatile u32 subtrahend;
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 response;

        asm {
            stw     r24, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x168)
            opword  0xFC0FA901
            opword  0x8C484680
        after3:
            mflr    r24
            lwz     r25, 0x0(r24)
            stw     r25, 0x0(r1)
            stw     r24, 0x4(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0x18C)
            opword  0xB7077404
            opword  MF_WORD(0x194)
        after4:
            mflr    r21
            lwz     r30, 0x0(r21)
            stw     r21, anchor
            lwz     r17, 0x8(r21)
            stw     r30, offset
            stw     r17, subtrahend
        }
        offset = offset - 0x5B;
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    }
}
#undef MF_FUNCTION

DoorUnlockStar::~DoorUnlockStar() {}

void DoorUnlockStar::setPos(const hel::math::Vector2& from, const hel::math::Vector2& to, const hel::math::Vector2& door) {
    mFrom = hel::math::Vector3(from.x, from.y, -2.5f);
    mTo = hel::math::Vector3(to.x, to.y, -2.5f);
    mDoorPos.x = door.x;
    mDoorPos.y = door.y;
}

void DoorUnlockStar::procAnim() {
    mModel.updateFrame();
    switch (mState) {
    case STATE_START:
        if (mModel.isAnimEnd()) {
            mModel.setAnimByName("Fly");
            mModel.start(true);
            mCounter.reset(60);
            mfSetupEffect();
            mSE.start(0x4BE);
            mState = STATE_FLY;
        }
        break;
    case STATE_FLY: {
        f32 ratio = getFlyPosRatio(mCounter.frame());
        mPos = mFrom * (1.0f - ratio) + mTo * ratio;
        mModel.setTrans(mPos);
        mCounter.advanceIfNotEnd();
        if (mCounter.isEnd()) {
            mModel.setAnimByName("Destroy");
            mModel.start(false);
            mEffect.release();
            if (mIsBoss) {
                mModel.model().nodeByName("BigStarL").setVisibility(false);
                mModel.model().nodeByName("BigStarL").setVisibilityBelow(false);
                mCounter.reset(200);
            } else {
                mSE.start(0x4BB);
            }
            mState = STATE_DESTROY;
        }
        break;
    }
    case STATE_DESTROY:
        mModel.setTrans(mTo);
        if (mIsBoss) {
            mModel.model().nodeByName("BigStarL").setVisibility(false);
            mModel.model().nodeByName("BigStarL").setVisibilityBelow(false);
            mCounter.advanceIfNotEnd();
            if (mCounter.isEnd()) {
                mModel.setVisibility(false);
                mComponent.bgFade().setFadeIn(10);
                mComponent.bgmController().unpause(core::BGM_CATEGORY_0, 0);
                mState = STATE_END;
            }
        } else if (mModel.isAnimEnd()) {
            mModel.setVisibility(false);
            mComponent.bgFade().setFadeIn(10);
            mSE.start(0x4BD);
            mComponent.bgmController().unpause(core::BGM_CATEGORY_0, 0);
            mState = STATE_END;
        }
        break;
    }
    if (mZoomHandle != 0) {
        updateZoom();
    }
}

void DoorUnlockStar::start() {
    mPos = hel::math::Vector3(mFrom.x, mFrom.y, -2.5f);
    mModel.setTrans(mPos);
    mModel.setVisibility(true);
    mModel.setAnimByName("Start");
    mModel.start(false);
    mComponent.bgFade().setColor(hel::common::Color(0, 0, 0, 150));
    mComponent.bgFade().setFadeOut(10);
    mSE.start(0x4BC);
    mState = STATE_START;
}

void DoorUnlockStar::start_Boss() {
    mIsBoss = true;
    start();
}

#define MF_FUNCTION setZoom__Q53scn4step7gimmick9lvmapdoor14DoorUnlockStarFbf
void DoorUnlockStar::setZoom(bool flag, f32 frame) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    f32 zoom;
    u32 word;
    u32 hash;
    u32 t;
    u32 last;
    u32 p;

    asm {
        bl      after1
        opword  MF_WORD(0x34)
        opword  0xACF1747D
    after1:
        mflr    r18
        lwz     r17, 0x0(r18)
        stw     r17, expected
    }
    _28 = flag;
    hash = 0xB3;
    hel::math::Vector2 center;
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x1C4C0E91
        opword  0x1C086590
        opword  MF_WORD(0x68)
    after2:
        mflr    r17
        lwz     r16, 0x0(r17)
        add     r16, r16, r17
        lwz     r19, 0xc(r17)
        stw     r16, start
        add     r19, r19, r16
        stw     r19, end
    }
    p = start;
    last = end;
    p -= 2;
    while (p != last - 2) {
        p += 2;
        hash = *(u16*)p ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 3;
    getCameraSetting(center, zoom);
    t = hash >> 11;
    hash ^= t;
    t = hash << 15;
    hash += t;
    t = expected;
    t = hash & ~t;
    word = expected;
    word = word & ~hash;
    word = t | word;
    hash = __cntlzw(word);
    word = hash >> 5;
    hash = word >> 6;
    hash = word - hash;
    if (hash == 0) {
        volatile u32 subtrahend;
        volatile u32 anchor;
        volatile u32 response;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0x60088A92
            opword  MF_WORD(0x118)
        after3:
            mflr    r15
            lwz     r19, 0x4(r15)
            stw     r19, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x13C)
            opword  0xA0CADC90
            opword  0xE857BD80
            opword  MF_WORD(0x148)
        after4:
            mflr    r14
            lwz     r29, 0x0(r14)
            stw     r14, anchor
            lwz     r24, 0xc(r14)
            stw     r29, offset
            stw     r24, subtrahend
        }
        offset = offset - 0x7D;
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    } else {
        mZoomHandle = mComponent.cameraController().setZoom(center, zoom, frame, false);
    }
}
#undef MF_FUNCTION

void DoorUnlockStar::updateZoom() {
    hel::math::Vector2 center;
    f32 zoom;
    getCameraSetting(center, zoom);
    mComponent.cameraController().updateZoom(mZoomHandle, center, zoom);
}

#define MF_FUNCTION unsetZoom__Q53scn4step7gimmick9lvmapdoor14DoorUnlockStarFv
void DoorUnlockStar::unsetZoom() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 size;
    u32 hash;
    u32 i;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x3191180C
        opword  0x7C967D80
        opword  MF_WORD(0x30)
        opword  0x24C29290
        opword  0xD8A5CF80
    after1:
        mflr    r20
        lwz     r15, 0xc(r20)
        lwz     r18, 0x0(r20)
        add     r18, r18, r20
        stw     r18, start
        add     r15, r15, r18
        stw     r15, end
    }
    hash = 0x811C9DC5;
    last = end;
    size = last - start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000181;
    }
    hash += hash << 3;
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0x19151E85
    after2:
        mflr    r28
        lwz     r26, 0x0(r28)
        stw     r26, expected
    }
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || mZoomHandle != 0) {
        mComponent.cameraController().unsetZoom(mZoomHandle);
    }
    mZoomHandle = 0;
}
#undef MF_FUNCTION

#define MF_FUNCTION isFlyEnd__Q53scn4step7gimmick9lvmapdoor14DoorUnlockStarCFv
bool DoorUnlockStar::isFlyEnd() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  0x38F96B80
        opword  0x230A200D
        opword  MF_WORD(0x2C)
        opword  0xA00CD080
        opword  0x546E5881
        opword  MF_WORD(0x38)
        opword  0x4F1ECC08
        opword  0xE86E6F00
    after1:
        mflr    r15
        lwz     r17, 0x14(r15)
        lwz     r14, 0x8(r15)
        stw     r14, end
        stw     r17, start
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x12A28B4A
    after2:
        mflr    r30
        lwz     r22, 0x0(r30)
        stw     r22, expected
    }
    limit = end - start + 1;
    base = start;
    hash = 0x811C9DDB;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash = expected ^ hash;
    hash = __cntlzw(hash);
    limit = hash >> 5;
    hash = limit >> 1;
    hash = limit - hash;
    if (hash == 0) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 addend;

        asm {
            stw     r16, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xF0)
            opword  0x01CA5A0C
        after3:
            mflr    r16
            lwz     r22, 0x0(r16)
            stw     r22, 0x0(r1)
            stw     r16, 0x4(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x110)
            opword  MF_WORD(0x114)
        after4:
            mflr    r29
            lwz     r18, 0x0(r29)
            lwz     r19, 0x4(r29)
            stw     r19, addend
            stw     r18, offset
            stw     r29, anchor
        }
        offset = offset + 0xF6;
        response = offset + addend;
        response = response + anchor;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        if (mState == STATE_DESTROY || mState == STATE_END) {
            return true;
        }
        return false;
    }
}
#undef MF_FUNCTION

// TODO: only the game's own part, 90 of 1060 instructions. The original also decodes four hidden objects here
// (docs/metafortress.md): it reads dcpl_0x064d085b, dcpl_0x1e29fd13 and dcpl_0xd33c62e7 and rewrites
// dcpl_0xd622c6e3, with its statements spread among these. ChallengeDoor::isUnlockEnd shows the form of one.
void DoorUnlockStar::getCameraSetting(hel::math::Vector2& center, f32& zoom) {
    f32 aspect = mComponent.cameraAccessor().projAspect(camera::KIND_0);
    f32 left = mPos.x - 3.0f;
    f32 right = 3.0f + mPos.x;
    f32 bottom = mPos.y - 3.0f;
    f32 top = 3.0f + mPos.y;
    if (_28) {
        f32 maxWidth = 9.0f * aspect;
        f32 limit = mDoorPos.x - 2.0f;
        if (left > limit) {
            left = limit;
            if (right - limit > maxWidth) {
                left = right - maxWidth;
            }
        }
        limit = 2.0f + mDoorPos.x;
        if (right < limit) {
            right = limit;
            if (limit - left > maxWidth) {
                right = maxWidth + left;
            }
        }
        limit = mDoorPos.y - 2.0f;
        if (bottom > limit) {
            bottom = limit;
            if (top - limit > 9.0f) {
                bottom = top - 9.0f;
            }
        }
        limit = 2.0f + mDoorPos.y;
        if (top < limit) {
            top = limit;
            if (limit - bottom > 9.0f) {
                top = 9.0f + bottom;
            }
        }
    }
    f32 x = 0.5f * (left + right);
    f32 y = 0.5f * (bottom + top);
    f32 height = top - bottom;
    f32 width = right - left;
    if (width > aspect * height) {
        height = width / aspect;
    }
    if (height < 8.0f) {
        height = 8.0f;
    }
    center.x = x;
    center.y = y;
    zoom = height;
}

f32 DoorUnlockStar::getFlyPosRatio(int frame) const {
    f32 total = 1830.0f;
    if (frame < 60) {
        return static_cast<f32>(frame * (frame + 1) / 2) / total;
    } else {
        return static_cast<f32>((frame - 59) * 60 + 1770) / total;
    }
}

void DoorUnlockStar::mfSetupEffect() {
    mEffect.requestN(static_cast<effect::Kind>(0x226), mModel.model().nodeByName("TopL"), false);
}

}}}}  // namespace scn::step::gimmick::lvmapdoor

// One of the hidden objects of the copy protection (docs/metafortress.md). Functions of other units reach it
// through an address they decode from inline data.
u32 dcpl_0x63f385c4_dcpl0_mfort6317_[4] = { 0x807B917A, 0xD89FC348, 0xAB508DC2, 0x59A825AA };
