#include "scn/step/enemy/goliathiceball/BrainFall.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/goliathiceball/StateFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

BrainFall::BrainFall(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFall::onStart() {
    obj().stateChanger().setNextState<StateFollow, Enemy*>(&obj());
    return true;
}

bool BrainFall::onLanding() {
    return false;
}

}}}}  // namespace scn::step::enemy::goliathiceball
