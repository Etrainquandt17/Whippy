#include "scn/step/enemy/craby/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/craby/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace craby {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWait::onLanding() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::craby
