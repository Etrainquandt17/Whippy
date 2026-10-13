#include "scn/step/enemy/babut/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/babut/StateFlySinCurve.h"
#include "scn/step/enemy/babut/StatePursuit.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    if (obj().variation() == 0x4d) {
        obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
    }
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::babut
