#include "scn/step/enemy/knucklejoe/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/knucklejoe/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onLanding() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::knucklejoe
