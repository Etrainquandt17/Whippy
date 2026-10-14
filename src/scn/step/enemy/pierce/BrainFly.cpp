#include "scn/step/enemy/pierce/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/pierce/StateFlyAround.h"
#include "scn/step/enemy/pierce/StateFlyPursuit.h"
#include "scn/step/enemy/pierce/StateFlySinCurve.h"
#include "scn/step/enemy/pierce/StateFlyWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    switch (obj().variation()) {
    default:
        obj().stateChanger().setNextState<StateFlyWait, Enemy*>(&obj());
        break;
    case 0xab:
        obj().stateChanger().setNextState<StateFlyAround, Enemy*>(&obj());
        break;
    case 0xac:
        obj().stateChanger().setNextState<StateFlyPursuit, Enemy*>(&obj());
        break;
    case 0xaa:
        obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
        break;
    }
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::pierce
