#include "scn/step/boss/goliath/StateDeadFall.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateDeadEnd.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateDeadFall::StateDeadFall(Boss* boss) : StateBase(boss), mFrame(0), mMoveFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x14);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    mStartPos = obj().location().pos();
    mGoalPos = obj().location().pos();
    mGoalPos.y += obj().param().goliath()._110;
}

StateDeadFall::~StateDeadFall() {}

void StateDeadFall::procAnim() {
    const Param& param = obj().param().goliath();
    if (mFrame < param._10C) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateDeadEnd, Boss*>(objPtr());
        return;
    }
    if (mMoveFrame < param._108) {
        mMoveFrame++;
    }
}

void StateDeadFall::procMove() {
    const Param& param = obj().param().goliath();
    f32 t = static_cast<f32>(mMoveFrame) / static_cast<f32>(param._108);
    obj().location().setPos(Math::LinearInterpolation(mStartPos, mGoalPos, t));
}

void StateDeadFall::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
