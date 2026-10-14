#include "scn/step/enemy/noddy/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace noddy {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWait::onLanding() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::noddy
