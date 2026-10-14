#include "scn/step/enemy/foley/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/foley/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::foley
