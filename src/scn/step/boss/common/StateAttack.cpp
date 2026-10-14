#include "scn/step/boss/common/StateAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace common {

StateAttack::StateAttack(Boss* boss, StateAttackDesc& desc, unsigned long scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
    Utility::ControlHateOnAction(obj());
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        Vector2 pos(mDesc._4.x * obj().target().getSign(), mDesc._4.y);
        Vector2 speed(mDesc._C.x * obj().target().getSign(), mDesc._C.y);
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + pos.toVector3());
    }
    if (obj().scriptTrigger().get(1)) {
        obj().move().setSpeedH(mDesc._14 * obj().target().getSign());
    }
    if (obj().scriptTrigger().get(2)) {
        obj().move().setSpeedH(mDesc._18 * obj().target().getSign());
    }
}

void StateAttack::procMove() {
    obj().move().groundDecel(mDesc._0);
}

void StateAttack::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::common
