#include "scn/step/enemy/common/BrainMahoroa2CallingShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateMahoroa2CallingShotFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainMahoroa2CallingShot::BrainMahoroa2CallingShot(Enemy& enemy, bool _8) : BrainBase(enemy), _8(_8) {}

bool BrainMahoroa2CallingShot::onStart() {
    obj().stateChanger().setNextState<StateMahoroa2CallingShotFollow, Enemy*, bool>(&obj(), _8);
    return true;
}

bool BrainMahoroa2CallingShot::onRecover() {
    obj().deadWithEffect();
    return true;
}

}
}
}
}
