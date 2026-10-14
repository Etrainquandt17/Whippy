#include "scn/step/enemy/foley/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/foley/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::foley
