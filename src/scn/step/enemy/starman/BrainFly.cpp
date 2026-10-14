#include "scn/step/enemy/starman/BrainFly.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/starman/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

bool BrainFly::onRecover() {
    return onStart();
}

void BrainFly::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::starman
