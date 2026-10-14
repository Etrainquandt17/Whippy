#include "scn/step/enemy/mahoroalowper/BrainLoop.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroalowper/StateLoop.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

BrainLoop::BrainLoop(Enemy& enemy) : BrainBase(enemy) {}

bool BrainLoop::onStart() {
    obj().stateChanger().setNextState<StateLoop, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroalowper
