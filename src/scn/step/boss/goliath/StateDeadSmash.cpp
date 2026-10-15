#include "scn/step/boss/goliath/StateDeadSmash.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateDead.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Manager.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateDeadSmash::StateDeadSmash(Boss* boss)
    : StateBase(boss), mIsPanelShown(true), mIsStaged(false), mIsSmash(false), mTime(boss->param().goliath()._D8), mFrame(0),
      mStartPos(), mGoalPos(), mRot(0.0f), mRotSpeed(0.0f) {
    const Param& param = obj().param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().hitStop().clear();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    if (obj().objColl().bodyColl().hit().isCollide()) {
        Vector2 attackPos = obj().objColl().bodyColl().damageInfo().attackPos();
        obj().target().setIsRightDir(attackPos.x > obj().location().pos().x);
        obj().model().rotCtrl().setRotHIntoTarget();
    }
    stagingBossDead();
    mStartPos = obj().location().pos();
    mGoalPos = obj().location().pos();
    mGoalPos.x = custom.landCtrl().getAdjustX(mGoalPos.x, 2.0f);
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    mGoalPos.z = param._EC;
}

StateDeadSmash::~StateDeadSmash() {
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().reset();
}

void StateDeadSmash::procAnim() {
    const Param& param = obj().param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsStaged) {
        stagingBossDead();
        return;
    }
    if (mIsPanelShown) {
        mIsPanelShown = false;
        Utility::DisappearBossPanel(obj());
        obj().soundSE().normal().start(0x384);
    }
    if (mFrame < mTime) {
        mFrame++;
    } else {
        if (mIsSmash) {
            obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
            return;
        }
        mIsSmash = true;
        mFrame = 0;
        mTime = param._DC;
        mRot = 0.0f;
        mStartPos = obj().location().pos();
        mGoalPos = mStartPos;
        mGoalPos.x = custom.landCtrl().getAdjustX(mGoalPos.x, 3.0f);
        mGoalPos.y += param._E8;
        mGoalPos.z += param._F0;
        obj().model().rotCtrl().setRotHTarget(0.0f);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    }
    if (!mIsSmash) {
        mRot += mRotSpeed;
        if (mRot < 0.0f) {
            mRot += 360.0f;
        }
        mRotSpeed -= param._F4;
        if (mRotSpeed < -param._F8) {
            mRotSpeed = -param._F8;
        }
    } else {
        f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
        mRot = Math::Interpolate(0.0f, -360.0f, Math::SinDegF(90.0f * t));
    }
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mRot, 0.0f, 0.0f)));
}

void StateDeadSmash::procMove() {
    const Param& param = obj().param().goliath();
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    if (!mIsSmash) {
        pos.y += param._E0 * Math::SinDegF(180.0f * t);
    } else {
        f32 u = 1.0f - Math::SinDegF(180.0f * t);
        f32 rate = 1.0f - u * u;
        pos.y += rate * param._E4;
    }
    obj().location().setPos(pos);
}

void StateDeadSmash::procFixPos() {}

void StateDeadSmash::stagingBossDead() {
    const Param& param = obj().param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsStaged && !Utility::IsHeroDeadStop(obj())) {
        mIsStaged = true;
        obj().comp().enemyManager().reqDeadAllEnemyForBoss();
        obj().comp().weaponManager().reqDeadByTeamNo(static_cast<ocoll::TeamNo>(1));
        obj().effect().back().releaseAndVanish();
        obj().effect().fore().releaseAndVanish();
        obj().model().reqScript(0x13);
        Utility::StagingBossDead(obj(), Vector3(param._FC));
        custom.hairCtrl().setAngry(false);
        custom.eyeCtrl().setAngry(false);
        custom.eyeCtrl().setKeepOpen();
        obj().model().updateMtx();
    }
}

}}}}  // namespace scn::step::boss::goliath
