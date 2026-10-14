#include "scn/step/enemy/goliathicicle/BrainFall.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/goliathicicle/StateFlyWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {

BrainFall::BrainFall(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFall::onStart() {
    obj().stateChanger().setNextState<StateFlyWait, Enemy*>(&obj());
    return true;
}

bool BrainFall::onLanding() {
    return false;
}

}}}}  // namespace scn::step::enemy::goliathicicle
