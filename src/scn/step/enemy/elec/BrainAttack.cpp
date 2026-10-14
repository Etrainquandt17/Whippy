#include "scn/step/enemy/elec/BrainAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/elec/StateChase.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::elec
