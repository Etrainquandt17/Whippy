#include "scn/step/enemy/sheld/BrainEscape.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sheld/StateEscape.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

BrainEscape::BrainEscape(Enemy& enemy) : BrainBase(enemy) {}

bool BrainEscape::onLanding() {
    obj().stateChanger().setNextState<StateEscape, Enemy*>(&obj());
    return true;
}

}
}
}
}
