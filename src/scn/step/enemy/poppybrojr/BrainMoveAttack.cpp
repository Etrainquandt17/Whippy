#include "scn/step/enemy/poppybrojr/BrainMoveAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/poppybrojr/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

BrainMoveAttack::BrainMoveAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMoveAttack::onStart() {
    obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    return true;
}

bool BrainMoveAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::poppybrojr
