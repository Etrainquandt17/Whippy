#include "scn/step/enemy/common/BrainMahoroa1.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/common/StateMahoroa1Appear.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainMahoroa1::BrainMahoroa1(Enemy& enemy, bool _8) : BrainBase(enemy), _8(_8) {}

bool BrainMahoroa1::onStart() {
    obj().stateChanger().setNextState<StateMahoroa1Appear, Enemy*, bool>(&obj(), _8);
    return true;
}

bool BrainMahoroa1::onRecover() {
    if (_8) {
        obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    }
    return true;
}

}
}
}
}
