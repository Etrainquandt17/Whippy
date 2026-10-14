#include "scn/step/enemy/coconutbomb/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/coconutbomb/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace coconutbomb {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::coconutbomb
