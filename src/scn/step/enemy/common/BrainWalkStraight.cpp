#include "scn/step/enemy/common/BrainWalkStraight.h"

#include "scn/step/chara/CliffChecker.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainWalkStraight::BrainWalkStraight(Enemy& enemy) : BrainBase(enemy) {
    obj().cliffChecker().setValid(false);
}

bool BrainWalkStraight::onLanding() {
    obj().stateChanger().setNextState<StateWalkStraight, Enemy*>(&obj());
    return true;
}

}
}
}
}
