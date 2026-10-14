#include "scn/step/enemy/owgulf/BrainFlyWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

BrainFlyWait::BrainFlyWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFlyWait::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainFlyWait::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::owgulf
