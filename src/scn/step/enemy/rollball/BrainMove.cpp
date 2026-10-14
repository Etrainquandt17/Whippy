#include "scn/step/enemy/rollball/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/rollball/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::rollball
