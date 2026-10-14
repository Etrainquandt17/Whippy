#include "scn/step/enemy/barbar/BrainWait.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/barbar/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::barbar
