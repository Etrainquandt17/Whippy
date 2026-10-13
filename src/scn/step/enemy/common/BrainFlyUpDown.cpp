#include "scn/step/enemy/common/BrainFlyUpDown.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFlyUpDown.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainFlyUpDown::BrainFlyUpDown(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFlyUpDown::onStart() {
    obj().stateChanger().setNextState<StateFlyUpDown, Enemy*>(&obj());
    return true;
}

bool BrainFlyUpDown::onRecover() {
    return onStart();
}

bool BrainFlyUpDown::onLanding() {
    obj().stateChanger().setNextState<StateFlyUpDown, Enemy*>(&obj());
    return true;
}

}
}
}
}
