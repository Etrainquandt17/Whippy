#include "scn/step/boss/roah/StateStorm.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateStormEnd.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

namespace {

const u32 OnOffChangeFrameTable[] = { 10, 90, 140, 250, 300, 490 };

}

StateStorm::StateStorm(Boss* boss, Config config)
    : StateBase(boss)
    , mCount(0)
    , mStormCount(0)
    , mBasePos()
    , mConfig(config)
    , mIsMoveStart(false)
    , mIsStorm(false)
    , mIsOn(true)
    , mOnOffIndex(1)
    , mOnCount(0)
    , mRotX(0.0f) {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mBasePos = obj().location().pos().getXY();
    obj().model().reqScript(15);
    custom.mahoroaCtrl().getCustom().reqMotionStorm();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().guard().setType(GUARD_TYPE_2);
    switch (mConfig._8) {
    case StormKind_UpDown:
        custom.rotCtrl().setRotXMax(param.mStormRotXMax);
        custom.rotCtrl().setRotYMax(90.0f);
        custom.rotCtrl().setFixRotRate(param.mStormFixRotRate);
        break;
    case StormKind_Circle:
        mRotX = custom.rotCtrl().getRotX();
        custom.rotCtrl().toInvalid();
        obj().model().model().nodes().at(1).localMtx().setRTMtx(
            hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(mRotX, 0.0f, 0.0f)) *
            hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, param.mRotYMax * obj().target().getSign(), 0.0f)));
        break;
    }
    custom.rotCtrl().resetLocalMtxTempRot();
}

StateStorm::~StateStorm() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.rotCtrl().setRotXMax(param.mRotXMax);
    custom.rotCtrl().setRotYMax(param.mRotYMax);
    custom.rotCtrl().setFixRotRate(param.mFixRotRate);
    custom.stormCtrl().toInvalid();
    obj().effect().state().releaseAndVanish();
}

void StateStorm::procAnim() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mStormCount < mConfig._0) {
        if (mIsStorm) {
            mStormCount++;
        }
    } else {
        StateStormEnd::Config config;
        config.mRotX = mRotX - 360.0f;
        config.mKind = mConfig._8;
        obj().stateChanger().setNextState<StateStormEnd, Boss*, StateStormEnd::Config>(objPtr(), config);
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsMoveStart = true;
        mCount = 0;
#ifdef VERSION_SUKK01
        obj().effect().state().requestN(static_cast<effect::Kind>(0x637), 4);
#else
        obj().effect().state().requestN(static_cast<effect::Kind>(0x636), 4);
#endif
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4CE), 4);
    }
    if (obj().scriptTrigger().get(1)) {
        mIsStorm = true;
        custom.stormCtrl().toValid(mConfig._0);
    }
    if (mConfig._8 == StormKind_Circle) {
        f32 t = static_cast<f32>(mStormCount) / static_cast<f32>(mConfig._0);
        f32 rotZ = (1.0f - hel::math::Math::CosDegF(90.0f * t)) * (1.0f - hel::math::Math::CosDegF(90.0f * t));
        if (Utility::IsVariationExtra(obj())) {
            f32 s = 1.0f - (1.0f - hel::math::Math::SinDegF(90.0f * t)) * (1.0f - hel::math::Math::SinDegF(90.0f * t));
            f32 base = hel::math::Math::InterpolationParamMinToMax(t);
            base = 540.0f * base - param.mStormRotZBack * hel::math::Math::SinDegF(180.0f * s);
            rotZ = param.mStormRotZSwing * hel::math::Math::SinDegF(180.0f * rotZ) + base;
        } else {
            rotZ = -(360.0f * t) + param.mStormRotZSwing * hel::math::Math::SinDegF(180.0f * rotZ);
        }
        mRotX = mRotX * (1.0f - param.mStormRotXRate) + 360.0f * t * param.mStormRotXRate;
        f32 rate = 1.0f - (1.0f - hel::math::Math::SinDegF(90.0f * t)) *
                              ((1.0f - hel::math::Math::SinDegF(90.0f * t)) * (1.0f - hel::math::Math::SinDegF(90.0f * t)));
        f32 side = 90.0f * obj().target().getSign();
        f32 front = param.mRotYMax * obj().target().getSign();
        f32 rotY = rate * (side - front) + front;
        obj().model().model().nodes().at(1).localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, 0.0f, rotZ)) *
                                                                 hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(mRotX, 0.0f, 0.0f)) *
                                                                 hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(0.0f, rotY, 0.0f)));
        custom.rotCtrl().setLocalMtxTempRot(mRotX, rotY, rotZ);
    }
}

void StateStorm::procMove() {
    const Param& param = obj().param().roah();
    if (!mIsStorm) {
        if (mIsMoveStart && mCount < param.mOarMoveFrame) {
            mCount++;
            f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mOarMoveFrame);
            f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
            hel::math::Vector2 pos = mBasePos;
            pos.x -= param.mOarMoveDistance * hel::math::Math::SinDegF(180.0f * rate);
            obj().location().setPos(pos.toVector3());
        }
    } else {
        f32 t = static_cast<f32>(mStormCount) / static_cast<f32>(mConfig._0);
        hel::math::Vector2 pos = mBasePos;
        if (mConfig._8 == StormKind_UpDown) {
            if (isOnOffStormKind()) {
                f32 fade = (1.0f - hel::math::Math::CosDegF(90.0f * t)) *
                                                 ((1.0f - hel::math::Math::CosDegF(90.0f * t)) *
                                                  ((1.0f - hel::math::Math::CosDegF(90.0f * t)) *
                                                   ((1.0f - hel::math::Math::CosDegF(90.0f * t)) * (1.0f - hel::math::Math::CosDegF(90.0f * t)))));
                f32 amplitude = mConfig._4 - fade * param.mStormAmplitudeDown;
                pos.y += amplitude * (0.5f * (hel::math::Math::SinDegF(1.5f * (360.0f * t) + 90.0f) - 1.0f));
            } else {
                t = hel::math::Math::InterpolationParamMinToMax(t);
                pos.y -= mConfig._4 * hel::math::Math::SinDegF(param.mStormPhase);
                pos.y += mConfig._4 * hel::math::Math::SinDegF(360.0f * t + param.mStormPhase);
            }
        }
        obj().location().setPos(pos.toVector3());
    }
}

void StateStorm::procFixPos() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mIsStorm) {
        obj().objColl().clearAttack();
        if (isOnOffStormKind()) {
            if (mOnOffIndex < 6 && mStormCount == OnOffChangeFrameTable[mOnOffIndex]) {
                if (mIsOn) {
                    if (mOnOffIndex != 5) {
                        obj().effect().state().releaseAndVanish();
#ifdef VERSION_SUKK01
                        obj().effect().state().requestN(static_cast<effect::Kind>(0x638), 4);
#else
                        obj().effect().state().requestN(static_cast<effect::Kind>(0x637), 4);
#endif
                        obj().model().reqScript(17);
                        custom.stormCtrl().toInvalid();
                    }
                } else {
#ifdef VERSION_SUKK01
                    obj().effect().state().requestN(static_cast<effect::Kind>(0x637), 4);
#else
                    obj().effect().state().requestN(static_cast<effect::Kind>(0x636), 4);
#endif
                    obj().effect().state().requestN(static_cast<effect::Kind>(0x4CE), 4);
                    obj().model().reqScript(16);
                    mOnCount = 0;
                }
                mOnOffIndex++;
                mIsOn = !mIsOn;
            }
        } else {
            mIsOn = true;
        }
        bool isAttack = mIsOn;
        if (isOnOffStormKind()) {
            mOnCount++;
            if (isAttack && mOnCount >= param.mStormOnFrame) {
                if (mOnCount == param.mStormOnFrame) {
                    custom.stormCtrl().toValid(mConfig._0);
                }
            } else {
                isAttack = false;
            }
        }
        if (isAttack) {
            hel::math::Vector3 dir = obj().model().model().nodes().at(4).worldRotate().mFront;
            if (!dir.isZeroLoose(0.00001f)) {
                dir.normalize();
            } else {
                dir = hel::math::Vector3::BASIS_X * -1.0f;
            }
            hel::math::Vector2 tip = dir.getXY() * param.mStormAttackLength;
            hel::math::Vector2 root = dir.getXY() * param.mStormAttackLengthNear;
            obj().objColl().setAttackType(0, static_cast< ::scn::step::ocoll::AttackType>(0x1F7));
            obj().objColl().addAttack(0, 4, param.mStormAttackRadius, hel::math::Vector2::ZERO, tip);
            obj().objColl().addAttack(0, 4, param.mStormAttackRadiusNear, root, tip);
        }
    }
}

bool StateStorm::isOnOffStormKind() {
    bool result = false;
    if (mConfig._8 == StormKind_UpDown && Utility::IsVariationExtra(obj())) {
        result = true;
    }
    return result;
}

}}}}  // namespace scn::step::boss::roah
