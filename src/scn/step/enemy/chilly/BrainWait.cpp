#include "scn/step/enemy/chilly/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/chilly/StateLookAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateLookAround, Enemy*>(&obj());
    return true;
}

}
}
}
}
