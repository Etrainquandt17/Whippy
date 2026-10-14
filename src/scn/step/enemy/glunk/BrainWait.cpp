#include "scn/step/enemy/glunk/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainWait::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::glunk
