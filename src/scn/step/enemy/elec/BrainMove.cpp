#include "scn/step/enemy/elec/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/elec/StateChase.h"
#include "scn/step/enemy/elec/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    if (obj().variation() == 0xb6) {
        obj().stateChanger().setNextState<StateMoveCCW, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveCWR, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::elec
