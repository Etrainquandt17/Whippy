#include "scn/step/enemy/blipper/BrainMove.h"

#include "scn/step/chara/Water.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/blipper/StateFall.h"
#include "scn/step/enemy/blipper/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    if (obj().water().isInWater()) {
        obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    return onStart();
}

}
}
}
}
