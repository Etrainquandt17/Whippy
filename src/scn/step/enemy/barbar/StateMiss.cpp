#include "scn/step/enemy/barbar/StateMiss.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/barbar/StateStepBack.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

StateMiss::StateMiss(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0xb);
}

void StateMiss::procAnim() {
    if (obj().kind() == 0x3a) {
        if (obj().model().isAllEnd()) {
            obj().stateChanger().setNextState<StateStepBack, Enemy*>(objPtr());
        }
    } else {
        obj().stateChanger().setNextState<StateStepBack, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::barbar
