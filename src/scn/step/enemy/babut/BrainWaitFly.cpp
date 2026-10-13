#include "scn/step/enemy/babut/BrainWaitFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/babut/StateFlySinCurve.h"
#include "scn/step/enemy/babut/StateHang.h"
#include "scn/step/enemy/babut/StatePursuit.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

BrainWaitFly::BrainWaitFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWaitFly::onStart() {
    obj().stateChanger().setNextState<StateHang, Enemy*>(&obj());
    return true;
}

bool BrainWaitFly::onRecover() {
    if (obj().variation() == 0x4c) {
        obj().stateChanger().setNextState<StateFlySinCurve, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StatePursuit, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::babut
