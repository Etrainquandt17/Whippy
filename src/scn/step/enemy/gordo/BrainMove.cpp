#include "scn/step/enemy/gordo/BrainMove.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/gordo/StateMoveCircle.h"
#include "scn/step/enemy/gordo/StateMoveSinCurve.h"
#include "scn/step/enemy/gordo/StateMoveStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    switch (obj().variation()) {
    case 0xd3:
    case 0xd4:
    case 0xd5:
    case 0xd6:
    case 0xd:
    case 0xe:
        obj().stateChanger().setNextState<StateMoveCircle, Enemy*>(&obj());
        break;
    case 0xb:
        obj().stateChanger().setNextState<StateMoveSinCurve, Enemy*>(&obj());
        break;
    default:
        obj().stateChanger().setNextState<StateMoveStraight, Enemy*>(&obj());
        break;
    }
    return true;
}

}
}
}
}
