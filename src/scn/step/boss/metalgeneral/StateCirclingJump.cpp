#include "scn/step/boss/metalgeneral/StateCirclingJump.h"

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
#include "scn/step/boss/metalgeneral/StateCircling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateCirclingJump::StateCirclingJump(Boss* boss) : StateBase(boss), mCount(0) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0xB);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    mGoalPos = mStartPos;
    mGoalPos.x += param._168 * obj().target().getSign();
    mGoalPos.y += param._16C;
}

StateCirclingJump::~StateCirclingJump() {}

void StateCirclingJump::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (mCount < param._164) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateCircling, Boss*>(objPtr());
    }
}

void StateCirclingJump::procMove() {
    const Param& param = obj().param().metalgeneral();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._164);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    f32 height = Math::SinDegF(180.0f * t);
    pos.y += height * param._170;
    obj().location().setPos(pos);
}

void StateCirclingJump::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
