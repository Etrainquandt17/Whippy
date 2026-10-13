#include "scn/step/enemy/kabu/BrainJump.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

BrainJump::BrainJump(Enemy& enemy) : BrainBase(enemy) {}

bool BrainJump::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::kabu
