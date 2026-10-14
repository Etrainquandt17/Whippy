#include "scn/step/boss/lowper/StateMoveToFar.h"

#include "g3d/NodeLocalMtxAccessor.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWaitFar.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateMoveToFar::StateMoveToFar(Boss* boss, f32 y)
    : StateBase(boss), mStartPos(), mGoalPos(), mCount(0), mOffset(Vector3(0.0f, y, 0.0f)) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    mStartPos = obj().location().pos();
    mGoalPos = obj().basePos().toVector3();
    mGoalPos.y += 4.0f;
    mGoalPos.z -= 80.0f;
    mGoalPos += mOffset;
    obj().model().reqScript(0);
    obj().model().rotCtrl().setRotHTarget(180.0f);
}

StateMoveToFar::~StateMoveToFar() {}

void StateMoveToFar::procAnim() {
    mCount++;
    if (mCount == 60) {
        obj().stateChanger().setNextState<StateWaitFar, Boss*>(objPtr());
    }
}

void StateMoveToFar::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / 60.0f;
    Vector3 pos;
    f32 sign = mStartPos.x > 0.0f ? 1.0f : -1.0f;
    f32 rateX = t * (-0.3f * Math::SinDegF(360.0f * t));
    rateX += t;
    pos.x = mStartPos.x * (1.0f - rateX) + mGoalPos.x * rateX;
    f32 swing = 4.0f * Math::SinDegF(180.0f * rateX);
    swing += (1.0f - t) * ((1.0f - t) * ((1.0f - t) * ((1.0f - t) * (3.0f * Math::SinDegF(180.0f * t)))));
    swing *= sign;
    pos.x += swing;
    f32 rateY = 0.5f * (1.0f - Math::CosDegF(180.0f * t));
    pos.y = mStartPos.y * (1.0f - rateY) + mGoalPos.y * rateY;
    f32 rateZ = 0.5f * (1.0f - Math::CosDegF(180.0f * t));
    pos.z = mStartPos.z * (1.0f - rateZ) + mGoalPos.z * rateZ;
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateMoveToFar::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
