#include "scn/step/enemy/twister/BrainRise.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/twister/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

BrainRise::BrainRise(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRise::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainRise::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::twister
