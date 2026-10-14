#include "scn/step/boss/roah/StateMove.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateMove::StateMove(Boss* boss, Config config) : StateBase(boss), mCount(0), mStartPos(), mGoalPos(), mConfig(config) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    mStartPos = obj().location().pos().getXY();
    mGoalPos = mConfig._4 + obj().comp().mainCamera().getCenter();
    if (mConfig._C) {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    } else {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    }
}

StateMove::~StateMove() {}

void StateMove::procAnim() {
    if (mCount < mConfig._0) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateMove::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    obj().location().setPos(Math::LinearInterpolation(mStartPos, mGoalPos, rate).toVector3());
}

void StateMove::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
