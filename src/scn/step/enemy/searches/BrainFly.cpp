#include "scn/step/enemy/searches/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/searches/StateFly.h"
#include "scn/step/enemy/searches/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace searches {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    switch (obj().variation()) {
    default:
        obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
        break;
    case 0xa5:
    case 0xa6:
        obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
        break;
    }
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::searches
