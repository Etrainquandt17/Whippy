#include "scn/step/enemy/sun/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sun/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace sun {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::sun
