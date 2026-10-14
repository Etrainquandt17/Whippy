#include "scn/step/boss/galactaknight/StateShuttleLoop.h"

#include "gobj/Anim.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateGlideSword.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateShuttleLoop::StateShuttleLoop(Boss* boss, bool isAttack)
    : StateBase(boss), mStartPos(boss->location().pos()) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (isAttack) {
        mGoalPos = Utility::GetHatedHeroPos(obj());
        Utility::ControlHateOnAction(obj());
    } else {
        mGoalPos.x = custom.landCtrl().getFrontOutSidePosX();
        mGoalPos.y = custom.landCtrl().getFloorY() + obj().param().galactaknight()._84;
    }
    obj().model().reqScript(0x26);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().worldCage().setIsValid(false);
}

StateShuttleLoop::~StateShuttleLoop() {
    obj().worldCage().setIsValid(true);
}

void StateShuttleLoop::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateGlideSword, Boss*, Vector3>(objPtr(), mGoalPos);
    }
}

// TODO: the code matches; compare.py reports the order of the constants: the original numbers the 0.0f of Vector3()
// behind this function's 1.0f, this numbers it first.
void StateShuttleLoop::procMove() {
    const Param& param = obj().param().galactaknight();
    f32 total = static_cast<f32>(obj().model().anim().totalFrame());
    f32 t = obj().model().anim().frame() / total;
    f32 rate = 1.5f * t + -0.5f * t * t;
    Vector3 offset;
    offset.x = param._68 * Math::SinDegF(rate * param._64);
    offset.x += t * param._70;
    offset.x *= obj().target().getSign();
    offset.y = param._6C * (1.0f - Math::CosDegF(rate * param._64));
    offset.y += t * param._74;
    offset += mStartPos;
    obj().location().setPos(offset);
}

void StateShuttleLoop::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
