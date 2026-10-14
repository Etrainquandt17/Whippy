#include "scn/step/enemy/pluid/BrainJump.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

BrainJump::BrainJump(Enemy& enemy) : BrainBase(enemy) {}

bool BrainJump::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::pluid
