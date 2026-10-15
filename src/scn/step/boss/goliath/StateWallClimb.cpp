#include "scn/step/boss/goliath/StateWallClimb.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateWallWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateWallClimb::StateWallClimb(Boss* boss, f32 height, u32 time) : StateBase(boss), mTime(time), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xC);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    mStartPos = obj().location().pos();
    mGoalPos = mStartPos;
    mGoalPos.y += height;
}

StateWallClimb::~StateWallClimb() {}

void StateWallClimb::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateWallWait, Boss*>(objPtr());
    }
}

void StateWallClimb::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    obj().location().setPos(Math::LinearInterpolation(mStartPos, mGoalPos, t));
}

void StateWallClimb::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
