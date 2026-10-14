#include "scn/step/enemy/tick/StateAttack.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace tick {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(8);
}

void StateAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::tick
