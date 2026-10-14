#include "scn/step/weapon/mahoroalaser/Custom.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroalaser/StateHide.h"
#include "scn/step/weapon/mahoroawarphole2/Custom.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::geo::Rect;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroalaser {

Custom::Custom(Weapon& weapon)
    : CustomBase(weapon)
    , mAttackers()
    , mWarpHoleStart()
    , mWarpHoleEnd()
    , mIsStartRequested(false)
    , mStartPos()
    , mEndPos()
    , mReadyFrame(0)
    , mMainFrame(1)
    , mScale(1.0f)
    , mIsStartEdge(true)
    , mIsEndEdge(true)
    , mIsMoveLimitRectValid(false)
    , mMoveLimitRect() {
    for (u32 i = 0; i < 4; i++) {
        // TODO: the original keeps the component in r31, the attacker in r30 and the zero of the initialisers in r29.
        mAttackers[i].construct<Component&, ::ocoll::SearchHit&>(obj().comp(), obj().objColl().searchHit());
    }
}

bool Custom::onInit() {
    obj().culling().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().rotCtrl().setValid(false);
    obj().stateChanger().setNextState<StateHide, Weapon*>(&obj());
    return true;
}

void Custom::onDead() {
    clearCapture();
    releaseWarpHole();
}

void Custom::start(u32 readyFrame, u32 mainFrame) {
    mReadyFrame = readyFrame;
    mMainFrame = mainFrame;
    mIsStartRequested = true;
}

const Vector3& Custom::startPos() const {
    return mStartPos;
}

const Vector3& Custom::endPos() const {
    return mEndPos;
}

void Custom::setStartPos(const Vector3& pos) {
    mStartPos = pos;
}

void Custom::setEndPos(const Vector3& pos) {
    mEndPos = pos;
}

f32 Custom::scale() const {
    return mScale;
}

void Custom::setScale(f32 scale) {
    mScale = scale;
}

bool Custom::isStartEdge() const {
    return mIsStartEdge;
}

void Custom::setIsStartEdge(bool isStartEdge) {
    mIsStartEdge = isStartEdge;
}

bool Custom::isEndEdge() const {
    return mIsEndEdge;
}

void Custom::setIsEndEdge(bool isEndEdge) {
    mIsEndEdge = isEndEdge;
}

void Custom::setMoveLimitRect(const Rect& rect) {
    // TODO: the original assigns the Rect, whose assignment hel/geo/Rect.h only declares.
    mMoveLimitRect._0 = rect._0;
    mMoveLimitRect._4 = rect._4;
    mMoveLimitRect._8 = rect._8;
    mMoveLimitRect._C = rect._C;
    mIsMoveLimitRectValid = true;
}

bool Custom::isMoveLimitRectValid() const {
    return mIsMoveLimitRectValid;
}

Rect Custom::getMoveLimitRect() const {
    return mMoveLimitRect;
}

bool Custom::isStartRequested() const {
    return mIsStartRequested;
}

u32 Custom::getReadyFrame() const {
    return mReadyFrame;
}

u32 Custom::getMainFrame() const {
    return mMainFrame;
}

void Custom::chkCapture() {
    for (u32 i = 0; i < 4; i++) {
        if (mAttackers[i].isConstruct() && !mAttackers[i]->isCapture() && mAttackers[i]->chkCaptureHero()) {
            mAttackers[i]->reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x15));
            break;
        }
    }
}

void Custom::startCapture() {
    for (u32 i = 0; i < 4; i++) {
        if (mAttackers[i].isConstruct()) {
            mAttackers[i]->setConstraintPos(mStartPos);
        }
    }
}

void Custom::endCapture() {
    Vector3 pos = mEndPos;
    Vector3 dir = mEndPos - mStartPos;
    if (!dir.isZeroLoose(0.00001f)) {
        dir.normalize();
        dir *= 1000.0f;
        pos = mStartPos + dir;
    }
    for (u32 i = 0; i < 4; i++) {
        if (mAttackers[i].isConstruct()) {
            mAttackers[i]->setConstraintPos(pos);
        }
    }
    for (u32 i = 0; i < 4; i++) {
        if (mAttackers[i].isConstruct() && mAttackers[i]->isCapture()) {
            mAttackers[i]->reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x16));
        }
    }
}

void Custom::clearCapture() {
    for (u32 i = 0; i < 4; i++) {
        if (mAttackers[i].isConstruct() && mAttackers[i]->isCapture()) {
            mAttackers[i]->clearCapture();
        }
    }
}

void Custom::generateWarpHoleStartPos() {
    if (!mIsStartEdge && !mWarpHoleStart.isAlive()) {
        mWarpHoleStart = generateWarpHole(mStartPos.getXY(), mEndPos.getXY());
    }
}

void Custom::generateWarpHoleEndPos() {
    if (!mIsEndEdge && !mWarpHoleEnd.isAlive()) {
        mWarpHoleEnd = generateWarpHole(mEndPos.getXY(), mStartPos.getXY());
    }
}

void Custom::releaseWarpHole() {
    if (mWarpHoleStart.isAlive()) {
        DynamicCastToRef<mahoroawarphole2::Custom, ICustom>(mWarpHoleStart->custom()).reqChangeStateEnd();
        mWarpHoleStart = ObjRefHandle<Weapon>();
    }
    if (mWarpHoleEnd.isAlive()) {
        DynamicCastToRef<mahoroawarphole2::Custom, ICustom>(mWarpHoleEnd->custom()).reqChangeStateEnd();
        mWarpHoleEnd = ObjRefHandle<Weapon>();
    }
}

void Custom::reqFlashWarpHoleStartPos() {
    if (mWarpHoleStart.isAlive()) {
        mahoroawarphole2::Custom& custom =
            DynamicCastToRef<mahoroawarphole2::Custom, ICustom>(mWarpHoleStart->custom());
        if (Utility::IsExtra(obj())) {
            custom.reqBlackFlash();
        } else {
            custom.reqFlash();
        }
    }
}

void Custom::reqFlashWarpHoleEndPos() {
    if (mWarpHoleEnd.isAlive()) {
        mahoroawarphole2::Custom& custom =
            DynamicCastToRef<mahoroawarphole2::Custom, ICustom>(mWarpHoleEnd->custom());
        if (Utility::IsExtra(obj())) {
            custom.reqBlackFlash();
        } else {
            custom.reqFlash();
        }
    }
}

ObjRefHandle<Weapon> Custom::generateWarpHole(const Vector2& pos, const Vector2& targetPos) {
    Desc desc(
        static_cast<Kind>(0x8E), obj().variation(), static_cast<ostop::Flag>(8), pos, Vector2::ZERO,
        obj().objColl().owner()
    );
    desc._24 = targetPos;
    ObjRefHandle<Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        obj().soundSE().start(0x41E);
    }
    return weapon;
}

void Custom::setupLocation() {
    Vector3 pos = startPos();
    pos.z -= 2.5f + 2.0f * static_cast<f32>(obj().variation());
    obj().location().setPos(pos);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::mahoroalaser
