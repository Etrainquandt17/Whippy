#include "scn/step/camera/MainCamera.h"

#include "gfx/Utility.h"
#include "hel/math/Math.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/DebugStepSettingProxy.h"
#include "scn/step/map/KindUtil.h"

using hel::geo::Rect;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace camera {

#define MF_FUNCTION __ct__Q43scn4step6camera10MainCameraFRQ33scn4step9Component
MainCamera::MainCamera(Component& component)
    : _38(0.0f)
    , _3C(0.0f)
    , _40(0.0f)
    , _44(0)
    , _48(0)
    , _4C(0.0f)
    , _50(0.0f)
    , _54(40.0f)
    , _58(0.0f)
    , _5C(0.0f)
    , _80(mParam.obj()._94)
    , _84(mParam.obj()._98)
    , _88(0.0f)
    , _8C(0.0f)
    , _98(mParam.obj()._9C)
    , _A4(true)
    , _A5(false)
    , _A8((f32)gfx::Utility::CurrentGameWidth() / (f32)gfx::Utility::CurrentGameHeight()) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 limit;
    u32 hash;
    u32 value;
    u32 i;
    f32 a;
    f32 b;
    f32 c;

    asm {
        bl      after1
        opword  MF_WORD(0x134)
        opword  0x747E7580
        opword  0x2076D890
        opword  MF_WORD(0x140)
        opword  0xF8965781
    after1:
        mflr    r19
        lwz     r21, 0xc(r19)
        lwz     r18, 0x0(r19)
        add     r21, r18, r21
        stw     r21, end
        stw     r18, start
    }
    _4C = map::KindUtil::IsLevelMap(component.context().mapKind) ? mParam.obj()._10 : mParam.obj()._0;
    _50 = map::KindUtil::IsLevelMap(component.context().mapKind) ? mParam.obj()._18 : mParam.obj()._8;
    limit = end - start + 1;
    base = start;
    _58 = map::KindUtil::IsLevelMap(component.context().mapKind) ? mParam.obj()._14 : mParam.obj()._4;
    hash = 0xC5;
    _5C = map::KindUtil::IsLevelMap(component.context().mapKind) ? mParam.obj()._1C : mParam.obj()._C;
    asm {
        bl      after2
        opword  MF_WORD(0x25C)
        opword  0x59975824
    after2:
        mflr    r18
        lwz     r26, 0x0(r18)
        stw     r26, expected
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        value = (hash << 4) ^ (hash >> 28);
        hash = value ^ *(u16*)(base + i - 1);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || map::KindUtil::IsLevelMap(component.context().mapKind)) {
        a = mParam.obj()._A4;
        b = mParam.obj()._AC;
    } else {
        a = mParam.obj()._A0;
        b = mParam.obj()._A8;
    }
    c = mParam.obj()._B0;
    _38 = a;
    _3C = a;
    _88 = b;
    _8C = c;
    _60 = hel::geo::Rect(10.0f, -10.0f, -10.0f, 10.0f);
    _70 = _60;
    setCameraRect(_60, 1.0f);
}
#undef MF_FUNCTION

Matrix34 MainCamera::viewMtx() const {
    Matrix34 mtx = Matrix34::CreateLookAt(viewEyePos(), Vector3::BASIS_Y, viewTargetPos());
    if (isReverseMode()) {
        Matrix34 scale = Matrix34::CreateScale(Vector3(1.0f, -1.0f, 1.0f));
        mtx = scale * mtx;
    }
    return mtx;
}

Vector3 MainCamera::viewTargetPos() const {
    Vector3 pos = originalViewTargetPos();
    pos += _90.toVector3();
    return pos;
}

Vector3 MainCamera::viewEyePos() const {
    Vector3 dir = Vector3::BASIS_Z;
    dir.rotate(Vector3::BASIS_X, 0.017453292f * -_88);
    dir.rotate(Vector3::BASIS_Y, 0.017453292f * _8C);
    return viewTargetPos() + dir * _38;
}

Matrix34 MainCamera::originalViewMtx() const {
    Matrix34 mtx = Matrix34::CreateLookAt(originalViewEyePos(), Vector3::BASIS_Y, originalViewTargetPos());
    if (isReverseMode()) {
        Matrix34 scale = Matrix34::CreateScale(Vector3(1.0f, -1.0f, 1.0f));
        mtx = scale * mtx;
    }
    return mtx;
}

Vector3 MainCamera::originalViewTargetPos() const {
    return getCenter().toVector3();
}

Vector3 MainCamera::originalViewEyePos() const {
    Vector3 dir = Vector3::BASIS_Z;
    dir.rotate(Vector3::BASIS_X, 0.017453292f * -_88);
    dir.rotate(Vector3::BASIS_Y, 0.017453292f * _8C);
    return originalViewTargetPos() + dir * _38;
}

Vector2 MainCamera::getCenter() const {
    return getViewRect().getCenter();
}

Vector2 MainCamera::getCenterBG() const {
    return _18.getCenter();
}

Vector2 MainCamera::getCenterCulling() const {
    return _28.getCenter();
}

void MainCamera::setDistance(f32 distance) {
    _38 = distance;
}

f32 MainCamera::getDistance() const {
    return _38;
}

void MainCamera::setTargetDistance(f32 distance) {
    _3C = distance;
    _40 = _38;
}

f32 MainCamera::getTargetDistance() const {
    return _3C;
}

void MainCamera::setPreDistance(f32 distance) {
    _40 = distance;
}

f32 MainCamera::getPreDistance() const {
    return _40;
}

void MainCamera::setTargetFrame(int frame) {
    _44 = frame;
    _48 = 0;
}

int MainCamera::getTargetFrame() const {
    return _44;
}

void MainCamera::setTargetCurrentFrame(int frame) {
    _48 = frame;
}

int MainCamera::getTargetCurrentFrame() const {
    return _48;
}

f32 MainCamera::getNear() const {
    return _4C;
}

f32 MainCamera::getNearBG() const {
    return _50;
}

f32 MainCamera::getNearDistance() const {
    return _54;
}

f32 MainCamera::getFar() const {
    return _58;
}

f32 MainCamera::getFarBG() const {
    return _5C;
}

void MainCamera::setNear(f32 value) {
    _4C = value;
}

void MainCamera::setNearBG(f32 value) {
    _50 = value;
}

void MainCamera::setNearDistance(f32 value) {
    _54 = value;
}

void MainCamera::setFar(f32 value) {
    _58 = value;
}

void MainCamera::setFarBG(f32 value) {
    _5C = value;
}

f32 MainCamera::getAspect() const {
    return _A8;
}

f32 MainCamera::getFovy() const {
    f32 height = getViewRect().getHeight();
    return Math::Atan2DegF(height, _38);
}

f32 MainCamera::getBaseFovy() const {
    return Math::Atan2DegF(_80, _38);
}

void MainCamera::setCameraRect(const Rect& rect, f32 rate) {
    Rect target(rect);
    if (_A4) {
        target.transInternal(_60);
    }
    target.adjustAspectShrink(getAspect());
    _8 = Math::LinearInterpolation(_8, target, rate);
}

void MainCamera::setCameraRectFirstZoom(const Rect& rect, f32 rate, const Rect& zoomRect, f32 zoomRate) {
    Rect target(rect);
    if (_A4) {
        target.transInternal(_60);
    }
    target.adjustAspectShrink(getAspect());
    Rect zoomTarget(zoomRect);
    if (_A4) {
        zoomTarget.transInternal(_60);
    }
    zoomTarget.adjustAspectShrink(getAspect());
    target = Math::LinearInterpolation(target, zoomTarget, zoomRate);
    _8 = Math::LinearInterpolation(_8, target, rate);
}

void MainCamera::setCameraRectBG(const Rect& rect, f32 rate) {
    Rect target(rect);
    target.transInternal(_60);
    target.adjustAspectShrink(getAspect());
    _18 = Math::LinearInterpolation(_18, target, rate);
}

void MainCamera::setCameraRectCulling(const Rect& rect, f32 rate) {
    Rect target(rect);
    target.transInternal(_60);
    target.adjustAspectShrink(getAspect());
    _28 = Math::LinearInterpolation(_28, target, rate);
}

#define MF_FUNCTION initWorldRect__Q43scn4step6camera10MainCameraFRCQ33hel3geo4Rect
void MainCamera::initWorldRect(const Rect& rect) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 size;
    u32 last;

    setWorldRect(rect);
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0x1CCFA380
        opword  0xD4F3CE91
    after1:
        mflr    r30
        lwz     r23, 0x0(r30)
        lwz     r14, 0x4(r30)
        stw     r14, start
        stw     r23, end
    }
    hash = 0x811C9E07;
    last = end;
    size = last - start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x70CA7736
    after2:
        mflr    r24
        lwz     r26, 0x0(r24)
        stw     r26, expected
    }
    hash = (hash & ~expected) | (expected & ~hash);
    hash = __cntlzw(hash);
    i = hash >> 5;
    hash = i + i * 0x34;
    if (hash == 0) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 key;

        asm {
            stw     r24, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xF0)
        after3:
            mflr    r24
            lwz     r25, 0x0(r24)
            stw     r25, 0x0(r1)
            stw     r24, 0x4(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0x10C)
            opword  0x9C575A91
            opword  MF_WORD(0x114)
        after4:
            mflr    r14
            lwz     r29, 0x8(r14)
            stw     r29, key
            lwz     r29, 0x0(r14)
            stw     r14, anchor
            stw     r29, offset
        }
        offset = offset ^ 0x91;
        response = offset ^ key;
        response = response + anchor;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    } else {
        _70 = _60;
    }
}
#undef MF_FUNCTION

void MainCamera::setWorldRect(const Rect& rect) {
    _60 = rect;
    setCameraRect(_8, 1.0f);
}

Rect MainCamera::getWorldRect() const {
    return _60;
}

Rect MainCamera::getWorldRectBG() const {
    return _70;
}

Rect MainCamera::getViewRect() const {
    Rect rect(_8);
    f32 height = _98;
    f32 width = height * _A8;
    rect._0 += height;
    rect._4 -= height;
    rect._8 -= width;
    rect._C += width;
    return rect;
}

Rect MainCamera::getViewRectBG() const {
    return _18;
}

f32 MainCamera::getRotDegX() const {
    return _88;
}

void MainCamera::setRotDegX(f32 deg) {
    _88 = deg;
}

void MainCamera::setRotDegX(f32 deg, f32 rate) {
    _88 = _88 * (1.0f - rate) + deg * rate;
}

f32 MainCamera::getRotDegY() const {
    return _8C;
}

void MainCamera::setRotDegY(f32 deg) {
    _8C = deg;
}

void MainCamera::setRotDegY(f32 deg, f32 rate) {
    _8C = _8C * (1.0f - rate) + deg * rate;
}

const Vector2& MainCamera::getOffset() const {
    return _90;
}

const Vector2& MainCamera::getOffsetBG() const {
    return _9C;
}

void MainCamera::setOffset(const Vector2& offset) {
    _90 = offset;
}

void MainCamera::setZoomOffset(f32 offset) {
    _98 = offset;
}

void MainCamera::setOffsetBG(const Vector2& offset) {
    _9C = offset;
}

// TODO: the link dropped this one, and nothing but its size (0x7C) is known.
Vector2 MainCamera::getLocationRateVec() const {
    Vector2 center = getCenter();
    return Vector2((center.x - _60._8) / _60.getWidth(), (center.y - _60._4) / _60.getHeight());
}

void MainCamera::setIsWorldRectValid(bool isValid) {
    _A4 = isValid;
}

void MainCamera::setIsReverseMode(bool isReverse) {
    _A5 = isReverse;
}

bool MainCamera::isReverseMode() const {
    if (DebugStepSettingProxy::GetGeneralSettingIsReverseWorld()) {
        return true;
    }
    return _A5;
}

}}}  // namespace scn::step::camera
