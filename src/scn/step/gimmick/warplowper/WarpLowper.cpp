// TODO: the constructor calls hel::math::Vector2's copy constructor, the unit's only visible use of it. The second
// use that keeps it a call is not written, so the unit takes the declarations.
#define HEL_MATH_VECTOR2_OUT_OF_LINE
#define MEM_EXPLICITSCOPEDPTR_DESTRUCT_INLINE

#include "scn/step/gimmick/warplowper/WarpLowper.h"

#include "effect/Requestor.h"
#include "g3d/CharaModelContext.h"
#include "g3d/MaterialAccessor.h"
#include "g3d/ResFileRepository.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Matrix44.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "metafortress.h"
#include "nw4r/math/math_arithmetic.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/StorageAccessor.h"
#include "scn/step/camera/CameraAccessor.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/gimmick/Util.h"
#include "scn/step/map/BinGmkGeneralEntry.h"
#include "scn/step/map/DataFile.h"
#include "scn/step/map/LandManager.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/map/MemManager.h"
#include "util/ObjList.h"

namespace g3d {
class Model;
}

// TODO: stand-ins. The original emits these two here and the link drops them, which leaves their strings in
// .data: g3d::ModelAccessor's destructor is implicit there and brings the list node's, and something gives
// the unit a general RuntimeTypeInfo (of which class is a guess).
template util::ObjListNode<g3d::Model, util::ObjListDummyType>::~ObjListNode();
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

using hel::math::Matrix34;
using hel::math::Matrix44;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace gimmick {
namespace warplowper {

namespace {

// TODO: map::BinGmkGeneralEntry goes on past the members its header has.
struct EntryTail {
    u32 _20;
    u32 _24;
};

}

WarpLowper::WarpLowper(const map::BinGmkGeneralEntry& entry, Component& component)
    : mParam("step/gimmick/WarpLowper")
    , mComponent(component)
    , mPos(entry._4.toMaproPos().toWorldPos())
    , _14(entry._14)
    , _18(entry._18)
    , _1C(0)
    , mResFile(component.mapMemManager().allocator())
    , mModel(component.mapMemManager().allocator())
    , _30(component)
    , _3CC(component)
    , mSE()
    , _7DC(0)
    , _7E0(false)
    , _7E1(false)
    , _7E2(StorageAccessor::GetWarpLowperEntered(mComponent, _1C))
    , _7E3(StorageAccessor::GetWarpLowperCleared(mComponent, _1C))
    , _7E4(component.mapDataFile().accessor().isEnableSFXMonotone())
    , _7E8(0)
    , mStop(mComponent)
    , mObjStop(mComponent)
    , _860(0)
    , _864(reinterpret_cast<const EntryTail*>(&entry + 1)->_20)
    , _868(reinterpret_cast<const EntryTail*>(&entry + 1)->_24)
    , _86C()
    , _874(false)
    , _875(false) {
    if (_7E4) {
        mResFile.construct(component.resFileRepos().get("step/gimmick/WarpLowperExit", false));
        const g3d::ResFileAccessor& resFile = mResFile.ref();
        mModel.construct(g3d::CharaModelContext(
            g3d::ResModelContext(resFile, "TopL"), g3d::CharaModelContext::DefaultModelBufferOption(), 0,
            g3d::CharaModelContext::DefaultNumView(), 2, component.mapMemManager().allocator(), false,
            g3d::CharaModelContext::DefaultOneAnimSlotWorkMemSize(), hel::common::FixedString<32>("GmkWarpLowperExit")));
    } else {
        mResFile.construct(component.resFileRepos().get("step/gimmick/WarpLowper", false));
        const char* name = component.context()._524.isExtraMode() ? "TopLEx" : "TopL";
        const g3d::ResFileAccessor& resFile = mResFile.ref();
        mModel.construct(g3d::CharaModelContext(
            g3d::ResModelContext(resFile, name), g3d::CharaModelContext::DefaultModelBufferOption(), 0,
            g3d::CharaModelContext::DefaultNumView(), 2, component.mapMemManager().allocator(), false,
            g3d::CharaModelContext::DefaultOneAnimSlotWorkMemSize(), hel::common::FixedString<32>("GmkWarpLowper")));
    }
    Vector3 pos = mPos.toVector3();
    pos.z = mParam->_8;
    mModel->setModelRTMtx(Matrix34::CreateTrans(pos));
    mModel->model().setVisibility(false);
    _30.changeLayer(core::DRAW_LAYER_KIND_4);
    _3CC.changeLayer(static_cast<core::DrawLayerKind>(2));
    if (!_7E3 && _7E2) {
        const g3d::ResFileAccessor& resFile = mResFile.ref();
        mModel->setAnim(0, resFile, "End");
        mModel->anim(0).start(false);
        mModel->model().setVisibility(true);
        _3CC.requestP(static_cast<effect::Kind>(0x1E7), pos, false);
        _30.requestP(static_cast<effect::Kind>(0x1E9), pos, false);
        _7E3 = true;
        StorageAccessor::SetWarpLowperCleared(mComponent, _1C, true);
    }
    if (_7E3) {
        _875 = true;
    }
    mStop.add(_30);
    mStop.add(_3CC);
    mfUpdateSRT();
}

WarpLowper::~WarpLowper() {
    mStop.remove(_3CC);
    mStop.remove(_30);
}

void WarpLowper::registerToRoot(g3d::Root& root) {
    if (!_874 && Util::InScreen(mComponent, mPos, 6.0f)) {
        mModel->registerToRoot(root);
    }
}

void WarpLowper::registerToRootFore(g3d::Root& root) {
    if (_874 && Util::InScreen(mComponent, mPos, 6.0f)) {
        mModel->registerToRoot(root);
    }
}

void WarpLowper::procBegin() {
    if (_7E8 == 0 && !_7E2 && mfDemoStartCheck()) {
        _875 = true;
    }
}

void WarpLowper::updateFrame() {
    if (mStop.isObjStopped()) {
        return;
    }
    if (Util::InScreen(mComponent, mPos, 6.0f)) {
        _30.procScreenIn();
        _3CC.procScreenIn();
    } else {
        _30.procScreenOut();
        _3CC.procScreenOut();
        if (_7E8 == 10) {
            return;
        }
    }
    mModel->updateFrame();
    {
        g3d::ModelAccessor model = mModel->model();
        _30.native().autoRequestOnUpdateFrame(model, mModel->anim(0));
    }
    mfProcessDemo();
    mModel->updateWorldMtxIfDirtyFlagOn();
}

void WarpLowper::onFrameEnd() {
    if (!_7E2 && !_7E0 && mfDemoStartCheck()) {
        mfStartDemo();
    }
}

void WarpLowper::updateUseGPU() {
    if (Util::InScreen(mComponent, mPos, 6.0f)) {
        mfUpdateSRT();
    }
}

bool WarpLowper::isHit(const Vector2& pos) const {
    if (_7E2) {
        return false;
    }
    if (_7E8 != 9 && _7E8 != 10) {
        return false;
    }
    f32 dx = mPos.x - pos.x;
    f32 dy = mPos.y - pos.y;
    f32 square = dx * dx + dy * dy;
    f32 distance = nw4r::math::FSqrt(square);
    return distance < mParam->_0;
}

void WarpLowper::onEntered() {
    _874 = true;
}

bool WarpLowper::isDiscardCopy() const {
    return !_7E4;
}

#define MF_FUNCTION mfRequestEffect__Q53scn4step7gimmick10warplowper10WarpLowperFv
void WarpLowper::mfRequestEffect() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 last;
    u32 i;
    u32 limit;

    Vector3 pos = mPos.toVector3();
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0xCDBA6601
    after1:
        mflr    r26
        lwz     r24, 0x0(r26)
        stw     r24, expected
        bl      after2
        opword  0x5AEDE40C
        opword  MF_WORD(0x4C)
        opword  0x049B9893
        opword  MF_WORD(0x54)
    after2:
        mflr    r27
        lwz     r29, 0x4(r27)
        lwz     r14, 0xc(r27)
        stw     r29, end
        stw     r14, start
    }
    hash = 0x811C9E29;
    pos.z = mParam->_8;
    last = end;
    limit = last - start + 1;
    i = -1;
    last--;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001AB;
    }
    _30.requestP(static_cast<effect::Kind>(0x1E5), pos, true);
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    if (hash != 0) {
        volatile u32 response;
        volatile u32 anchor;
        volatile u32 offset;
        volatile u32 unused;

        asm {
            bl      after3
            opword  0x18BE4190
            opword  0xB88B6281
            opword  MF_WORD(0x10C)
        after3:
            mflr    r23
            lwz     r15, 0x8(r23)
            stw     r15, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r15, -0x4(r1)
            stw     r23, -0x8(r1)
            mtlr    r15
            bl      after4
            opword  MF_WORD(0x130)
            opword  0xBC69B780
            opword  MF_WORD(0x138)
        after4:
            mflr    r15
            stw     r15, anchor
            lwz     r22, 0x0(r15)
            stw     r22, offset
            lwz     r20, 0x8(r15)
            stw     r20, unused
        }
        offset = offset - 0xAF;
        unused = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    } else {
        _3CC.requestP(static_cast<effect::Kind>(0x1E6), pos, true);
    }
}
#undef MF_FUNCTION

u32 WarpLowper::stepShift() const {
    return _14;
}

u32 WarpLowper::portalNo() const {
    return _18;
}

const Vector2& WarpLowper::pos() const {
    return mPos;
}

void WarpLowper::setGuard(bool guard) {
    _7E1 = guard;
}

bool WarpLowper::isAppearAlready() const {
    return _875;
}

bool WarpLowper::mfDemoStartCheck() const {
    bool start = false;
    if (mfGetIsBroken() && !_7E1) {
        start = true;
    }
    return start;
}

bool WarpLowper::mfGetIsBroken() const {
    bool broken = false;
    if (!mComponent.mapLandManager().native().isExistLand(mPos) && !mComponent.mapLandManager().native().isExistMoveLand(mPos)) {
        broken = true;
    }
    return broken;
}

void WarpLowper::mfStartWaitMain() {
    mModel->setAnim(0, mResFile.ref(), "WaitMain");
    mModel->anim(0).start(true);
    mModel->model().setVisibility(true);
    _7E8 = 10;
    onAnimStart();
}

#define MF_FUNCTION onAnimStart__Q53scn4step7gimmick10warplowper10WarpLowperFv
void WarpLowper::onAnimStart() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 tail;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x42B6D229
    after1:
        mflr    r17
        lwz     r19, 0x0(r17)
        stw     r19, expected
        bl      after2
        opword  0xB46E4E80
        opword  MF_WORD(0x48)
        opword  0x70881291
        opword  MF_WORD(0x50)
        opword  0x54736C80
    after2:
        mflr    r17
        lwz     r18, 0xc(r17)
        lwz     r16, 0x4(r17)
        add     r18, r16, r18
        stw     r18, end
        stw     r16, start
    }
    word = start;
    tail = end;
    for (; word != tail; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001AB;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash != 0) {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 addend;

        asm {
            bl      after3
            opword  0x5D3B6A0D
            opword  0x48D9C793
            opword  0x88126F01
            opword  MF_WORD(0xE4)
        after3:
            mflr    r24
            lwz     r18, 0xc(r24)
            stw     r18, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r18, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r18
            bl      after4
            opword  MF_WORD(0x108)
            opword  MF_WORD(0x10C)
        after4:
            mflr    r15
            stw     r15, anchor
            lwz     r21, 0x0(r15)
            stw     r21, offset
            lwz     r18, 0x4(r15)
            stw     r18, addend
        }
        offset = offset - 0xAA;
        response = offset + addend;
        response = response + anchor;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        g3d::ModelAccessor model = mModel->model();
        _30.native().autoRequestOnSetFrame(model, mModel->anim(0));
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION mfStartDemo__Q53scn4step7gimmick10warplowper10WarpLowperFv
void WarpLowper::mfStartDemo() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x68201080
        opword  0x1F59F00A
        opword  MF_WORD(0x30)
        opword  0xEC005D80
    after1:
        mflr    r29
        lwz     r17, 0x0(r29)
        lwz     r28, 0xc(r29)
        add     r17, r17, r29
        add     r28, r28, r17
        stw     r17, start
        stw     r28, end
    }
    word = start;
    tail = end;
    hash = 0;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == tail) {
            break;
        }
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0xF77E2B9D
    after2:
        mflr    r17
        lwz     r19, 0x0(r17)
        stw     r19, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    _7E0 = expected == hash;
    _7E8 = 1;
    _86C.reset(_864);
    mfRequestEffect();
}
#undef MF_FUNCTION

void WarpLowper::mfProcessDemo() {
    switch (_7E8) {
    case 0:
        if (!_7E2 && mfDemoStartCheck()) {
            _7E0 = true;
            _875 = true;
            mfStartWaitMain();
            mfRequestEffect();
        } else {
            _7E8 = 11;
        }
        break;
    case 1:
        _86C.advanceIfNotEnd();
        if (_86C.isEnd()) {
            if (mObjStop.request(static_cast<ostop::Flag>(0x11FF))) {
                mStop.setSpecial();
                _7E8 = 3;
            } else {
                _7E8 = 2;
            }
        }
        break;
    case 2:
        if (mObjStop.request(static_cast<ostop::Flag>(0x11FF))) {
            mStop.setSpecial();
            _7E8 = 3;
        }
        break;
    case 3:
        _86C.advanceIfNotEnd();
        if (_86C.isEnd()) {
            _7E8 = 4;
            f32 zoom = mParam->_C;
            _860 = mComponent.cameraController().setZoom(mPos, _868, zoom);
            _86C.reset(mParam->_10);
        }
        break;
    case 4:
        _86C.advanceIfNotEnd();
        if (_86C.isEnd()) {
            _7E8 = 5;
            mModel->setAnim(0, mResFile.ref(), "Start");
            mModel->anim(0).start(false);
            mModel->model().setVisibility(true);
            onAnimStart();
        }
        break;
    case 5: {
        if (mModel->anim(0).frame() == mParam.obj()._4) {
            mSE.start(0x16E);
        }
        if (mModel->anim(0).isAnimEnd()) {
            mModel->setAnim(0, mResFile.ref(), "WaitStart");
            mModel->anim(0).start(false);
            _7E8 = 6;
            _86C.reset(mParam->_14);
        }
        break;
    }
    case 6:
        _86C.advanceIfNotEnd();
        if (_86C.isEnd()) {
            _7E8 = 7;
            mComponent.cameraController().unsetZoom(_860);
            _86C.reset(mParam->_18);
        }
        break;
    case 7:
        _86C.advanceIfNotEnd();
        if (_86C.isEnd()) {
            _7E8 = 8;
            onAnimStart();
            _86C.reset(mParam->_1C);
        }
        break;
    case 8:
        _86C.advanceIfNotEnd();
        if (_86C.isEnd()) {
            _7E8 = 9;
            mObjStop.release();
            mStop.unsetSpecial();
        }
        break;
    case 9:
        if (mModel->anim(0).isAnimEnd()) {
            mfStartWaitMain();
        }
        break;
    }
}

void WarpLowper::mfUpdateSRT() {
    if (_7E4) {
        return;
    }
    f32 scale = mParam->_20;
    // TODO: the original builds this pair in place while the two vectors below call their constructor, so it is
    // not a third hel::math::Vector2(f32, f32); what it is, is not known.
    hel::math::Vec2 half;
    half.x = 416.0f;
    half.y = 228.0f;
    Matrix44 proj = mComponent.cameraAccessor().projConvMtx(static_cast<camera::Kind>(0));
    Vector3 projected = proj.mulVec(mPos.toVector3());
    Vector2 screen(projected.x, projected.y);
    screen.x *= half.x;
    screen.y *= half.y;
    Vector2 scaled(screen.x * scale, screen.y * scale);
    Matrix34 mtx;
    mtx.setT(scaled.toVector3());
    const g3d::MaterialAccessor& material = mModel->model().materialByName("RipC");
    material.texSRTSetEffectMtx(0, mtx);
    material.texSRTEndEdit();
}

}
}
}
}
