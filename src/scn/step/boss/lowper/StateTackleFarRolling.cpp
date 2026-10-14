#include "scn/step/boss/lowper/StateTackleFarRolling.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateTackleFarRolling::StateTackleFarRolling(Boss* boss)
    : StateBase(boss), mCount(0), mStartY(0.0f), mGoalY(0.0f), mX(0.0f), mRotX(0.0f), mRotY(0.0f), mRotSpeed(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    mStartY = 4.0f + obj().basePos().y;
    mGoalY = 0.5f + obj().basePos().y;
    mX = obj().location().pos().x;
    obj().model().reqScript(0xC);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    custom.enemyCtrl().setBarrierAngle(0.0f);
}

StateTackleFarRolling::~StateTackleFarRolling() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.enemyCtrl().resetBarrierAngle();
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateTackleFarRolling::procAnim() {
    mCount++;
    if (mCount == 90) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    mRotX = Math::LinearInterpolation(mRotX, 90.0f, 0.1f);
    mRotSpeed += 0.5f;
    if (mRotSpeed >= 20.0f) {
        mRotSpeed = 20.0f;
    }
    mRotY += mRotSpeed;
    if (mRotY >= 360.0f) {
        mRotY -= 360.0f;
    }
    NodeAccessor node = obj().model().model().nodes().at(3);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mRotX, 0.0f, 0.0f)) *
                             Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRotY, 0.0f)));
}

void StateTackleFarRolling::procMove() {
    f32 t = static_cast<f32>(mCount) / 90.0f;
    Vector3 pos;
    pos.x = mX;
    f32 sin = Math::SinDegF(180.0f * t);
    f32 rate = 1.0f - sin;
    if (t > 0.5f) {
        rate *= 0.5f;
    }
    pos.y = Math::LinearInterpolation(mGoalY, mStartY, rate);
    pos.z = -80.0f * (1.0f - t) + 80.0f * t;
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateTackleFarRolling::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
