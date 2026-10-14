#include "scn/step/enemy/lanzer/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/lanzer/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onLanding() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::lanzer
