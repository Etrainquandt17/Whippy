#include "scn/step/boss/metalgeneral/StateCenterJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateCenterJump::StateCenterJump(Boss* boss) : StateBase(boss), mCount(0) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xB);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    mGoalPos = obj().basePos().toVector3();
    mGoalPos.x += param._30;
    mGoalPos.y += param._134;
    bool isRight = mGoalPos.x - mStartPos.x > 0.0f;
    obj().target().setIsRightDir(isRight);
}

StateCenterJump::~StateCenterJump() {}

void StateCenterJump::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (mCount < param._130) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateCenterJump::procMove() {
    const Param& param = obj().param().metalgeneral();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._130);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    f32 height = Math::SinDegF(180.0f * t);
    pos.y += height * param._138;
    obj().location().setPos(pos);
}

void StateCenterJump::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
