#include "scn/step/weapon/roahoar/StateMoveStart.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahoar/Param.h"
#include "scn/step/weapon/roahoar/StatePursuit.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

StateMoveStart::StateMoveStart(Weapon* weapon) : StateBase(weapon), mFrame(0), mStartFrame(0) {
    const Param& param = obj().param().roahOar();
    obj().model().reqScript(1);
    mStartFrame = param._18 + param._1C * obj().variation();
}

void StateMoveStart::procAnim() {
    const Param& param = obj().param().roahOar();
    mFrame++;
    if (mFrame == mStartFrame) {
        obj().move().setSpeedH(param._20);
    }
    if (mFrame >= mStartFrame && mFrame % 5 == 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(0));
    }
    if (mFrame == mStartFrame + param._14) {
        obj().stateChanger().setNextState<StatePursuit, Weapon*>(objPtr());
    }
}

void StateMoveStart::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Create(0.0f);
    obj().move().decel(decel);
}

void StateMoveStart::procFixPos() {}

}}}}  // namespace scn::step::weapon::roahoar
