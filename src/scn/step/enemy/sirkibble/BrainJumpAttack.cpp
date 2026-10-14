#include "scn/step/enemy/sirkibble/BrainJumpAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sirkibble/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

BrainJumpAttack::BrainJumpAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainJumpAttack::onLanding() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::sirkibble
