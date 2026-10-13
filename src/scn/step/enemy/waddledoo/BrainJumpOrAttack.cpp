#include "scn/step/enemy/waddledoo/BrainJumpOrAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

BrainJumpOrAttack::BrainJumpOrAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainJumpOrAttack::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

void BrainJumpOrAttack::update() {
    Utility::ChkNururiTurn(obj());
    Utility::ChkCliffTurn(obj());
}

}}}}  // namespace scn::step::enemy::waddledoo
