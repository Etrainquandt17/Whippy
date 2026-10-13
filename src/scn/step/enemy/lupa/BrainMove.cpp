#include "scn/step/enemy/lupa/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/lupa/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}
}
}
}
