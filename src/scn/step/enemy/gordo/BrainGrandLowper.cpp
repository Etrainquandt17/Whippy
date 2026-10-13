#include "scn/step/enemy/gordo/BrainGrandLowper.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/gordo/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

}
}
}
}
