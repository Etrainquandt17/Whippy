#include "scn/step/enemy/owgulf/BrainFlyStraight.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/owgulf/StateFlyStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

BrainFlyStraight::BrainFlyStraight(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFlyStraight::onStart() {
    obj().stateChanger().setNextState<StateFlyStraight, Enemy*>(&obj());
    return true;
}

bool BrainFlyStraight::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::owgulf
