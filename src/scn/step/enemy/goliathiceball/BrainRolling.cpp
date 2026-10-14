#include "scn/step/enemy/goliathiceball/BrainRolling.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/goliathiceball/StateRollingFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

BrainRolling::BrainRolling(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRolling::onStart() {
    obj().stateChanger().setNextState<StateRollingFall, Enemy*>(&obj());
    return true;
}

bool BrainRolling::onLanding() {
    return false;
}

}}}}  // namespace scn::step::enemy::goliathiceball
