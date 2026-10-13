#include "scn/step/enemy/aquarock/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/aquarock/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::aquarock
