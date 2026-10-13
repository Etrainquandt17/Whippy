#include "scn/step/enemy/common/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

bool BrainFly::onLanding() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::common
