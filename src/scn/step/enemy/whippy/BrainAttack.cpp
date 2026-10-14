#include "scn/step/enemy/whippy/BrainAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace whippy {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::whippy
