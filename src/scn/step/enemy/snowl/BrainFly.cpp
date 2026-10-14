#include "scn/step/enemy/snowl/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/snowl/StateFlyAround.h"
#include "scn/step/enemy/snowl/StateFlyStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace snowl {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    if (obj().variation() == 0xba) {
        obj().stateChanger().setNextState<StateFlyStraight, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFlyAround, Enemy*>(&obj());
    }
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::snowl
