#include "scn/step/enemy/blipper/BrainJump.h"

#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/blipper/StateDive.h"
#include "scn/step/enemy/blipper/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

BrainJump::BrainJump(Enemy& enemy) : BrainBase(enemy) {}

bool BrainJump::onStart() {
    if (obj().water().isInWater()) {
        obj().stateChanger().setNextState<StateDive, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    }
    return true;
}

bool BrainJump::onRecover() {
    return onStart();
}

}
}
}
}
