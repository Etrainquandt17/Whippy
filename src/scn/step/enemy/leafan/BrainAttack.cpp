#include "scn/step/enemy/leafan/BrainAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/leafan/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace leafan {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::leafan
