#include "scn/step/enemy/bladeknight/BrainGrandLowper.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/bladeknight/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

}
}
}
}
