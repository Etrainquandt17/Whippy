#include "scn/step/enemy/togekuki/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/togekuki/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::togekuki
