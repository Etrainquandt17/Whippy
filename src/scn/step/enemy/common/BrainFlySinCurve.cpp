#include "scn/step/enemy/common/BrainFlySinCurve.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFlySinCurve.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainFlySinCurve::BrainFlySinCurve(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFlySinCurve::onStart() {
    obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
    return true;
}

bool BrainFlySinCurve::onRecover() {
    obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
    return true;
}

bool BrainFlySinCurve::onLanding() {
    obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
    return true;
}

}
}
}
}
