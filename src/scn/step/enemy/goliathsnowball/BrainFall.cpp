#include "scn/step/enemy/goliathsnowball/BrainFall.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/goliathsnowball/StateFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathsnowball {

BrainFall::BrainFall(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFall::onStart() {
    obj().stateChanger().setNextState<StateFollow, Enemy*>(&obj());
    return true;
}

bool BrainFall::onLanding() {
    return false;
}

}}}}  // namespace scn::step::enemy::goliathsnowball
