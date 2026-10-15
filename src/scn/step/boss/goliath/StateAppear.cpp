#include "scn/step/boss/goliath/StateAppear.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/hero/Manager.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateAppear::StateAppear(Boss* boss)
    : StateBase(boss), mIsWaitDemoReady(true), mIsGameStarted(false), mIsBgmStarted(false), mIsCameraLocked(false), mWaitFrame(0),
      mFrame(0), mRot(0.0f), mRotSpeed(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().goliath();
    Utility::TurnHatedHero(obj());
    obj().model().reqScript(5);
    obj().bgmCtrl().startBossDemo();
    obj().invincible().setPermNoFlash();
    obj().guard().setType(static_cast<GuardType>(6));
    obj().location().setPos(obj().basePos().toVector3() + Vector3(param._7C));
    obj().mapColl().reset();
    obj().model().updateMtx();
    obj().invincible().setPermNoFlash();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    if (Utility::IsStagingFirstAppear(obj())) {
        Utility::StagingFirstAppearStart(obj());
    } else {
        obj().model().setVisibility(true);
        obj().shadow().setVisibility(true);
        obj().model().reqScript(5);
        mIsWaitDemoReady = false;
    }
}

StateAppear::~StateAppear() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().reset();
}

void StateAppear::procAnim() {
    const Param& param = obj().param().goliath();
    if (Utility::IsStagingFirstAppear(obj()) && Utility::IsAppearDemoCancelRequested(obj())) {
        startGame();
        startBgm();
        setCameraLock();
        obj().location().setPos(obj().basePos().toVector3());
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mIsWaitDemoReady) {
        if (obj().comp().heroManager().isBossDemoReady()) {
            if (mWaitFrame < param._70) {
                mWaitFrame++;
            } else {
                mIsWaitDemoReady = false;
                obj().model().setVisibility(true);
                obj().shadow().setVisibility(true);
                obj().model().reqScript(5);
            }
        }
    } else {
        if (mFrame < param._6C) {
            mFrame++;
            updateRotate();
            if (mFrame == param._6C) {
                obj().model().model().nodes().at(1).localMtx().reset();
                if (Utility::IsStagingFirstAppear(obj())) {
                    obj().model().reqScript(6);
                } else {
                    obj().model().reqScript(1);
                }
            }
        }
        if (obj().scriptTrigger().get(0)) {
            startGame();
        }
        if (obj().scriptTrigger().get(1)) {
            startBgm();
        }
        if (obj().model().isAllEnd()) {
            setCameraLock();
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateAppear::procMove() {
    const Param& param = obj().param().goliath();
    f32 t = 1.0f - static_cast<f32>(mFrame) / static_cast<f32>(param._6C);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 offset(param._7C.x * t, param._7C.y * rate, param._7C.z * t);
    obj().location().setPos(obj().basePos().toVector3() + offset);
}

void StateAppear::procFixPos() {}

void StateAppear::startGame() {
    if (!mIsGameStarted) {
        mIsGameStarted = true;
        Utility::AppearBossPanel(obj());
        if (Utility::IsStagingFirstAppear(obj())) {
            Utility::StagingFirstAppearEnd(obj());
        }
    }
}

void StateAppear::startBgm() {
    if (!mIsBgmStarted) {
        mIsBgmStarted = true;
        obj().bgmCtrl().startBossBattleNormal();
    }
}

void StateAppear::setCameraLock() {
    if (!mIsCameraLocked) {
        mIsCameraLocked = true;
        DynamicCastToRef<Custom, ICustom>(obj().custom()).cameraCtrl().startAppearEnd();
    }
}

void StateAppear::updateRotate() {
    const Param& param = obj().param().goliath();
    mRot += mRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    mRotSpeed += param._74;
    mRotSpeed = Math::LimitMax(mRotSpeed, param._78);
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mRot, 0.0f, 0.0f)));
}

}}}}  // namespace scn::step::boss::goliath
