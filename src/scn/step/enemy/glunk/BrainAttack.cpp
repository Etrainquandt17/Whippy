#include "scn/step/enemy/glunk/BrainAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::glunk
