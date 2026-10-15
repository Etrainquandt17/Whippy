#include "scn/step/boss/goliath/StateEnergyBallJump.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateEnergyBallCharge.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateEnergyBallJump::StateEnergyBallJump(Boss* boss, u32 _1, u32 _2, f32 _3)
    : StateBase(boss), mFrame(0), _C(_1), _10(_2), _14(_3), mStartPos(boss->location().pos()) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = custom.landCtrl().getCenterX();
    mGoalPos.y = custom.landCtrl().getFloorYWithBump() + obj().param().goliath()._BC;
    obj().model().reqScript(0x2B);
    obj().model().rotCtrl().initRotH(0.0f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateEnergyBallJump::~StateEnergyBallJump() {}

void StateEnergyBallJump::procAnim() {
    if (mFrame < obj().param().goliath()._B8) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateEnergyBallCharge, Boss*, u32, u32, f32>(objPtr(), _C, _10, _14);
    }
}

void StateEnergyBallJump::procMove() {
    f32 rate;
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(obj().param().goliath()._B8);
    f32 u = 1.0f - Math::SinDegF(90.0f * t);
    rate = 1.0f - u * u;
    Vector3 pos;
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, rate);
    pos.z = mStartPos.z;
    obj().location().setPos(pos);
}

void StateEnergyBallJump::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
