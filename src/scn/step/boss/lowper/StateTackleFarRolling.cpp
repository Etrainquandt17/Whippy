#include "scn/step/boss/lowper/StateTackleFarRolling.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

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
    custom.collisionCtrl().setState(CollisionCtrl::STATE_TACKLE_FAR_ROLLING);
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
