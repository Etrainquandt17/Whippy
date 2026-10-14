#include "scn/step/enemy/hothead/BrainAttack.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    if (obj().variation() == 0x11b || obj().variation() == 0x11c) {
        obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
        return true;
    }
    return false;
}

bool BrainAttack::onRecover() {
    return onStart();
}

bool BrainAttack::onLanding() {
    return onStart();
}

void BrainAttack::update() {
    if (obj().variation() == 0x11b || obj().variation() == 0x11c) {
        Utility::ChkNururiTurn(obj());
        Utility::ChkCliffTurn(obj());
    }
}

}}}}  // namespace scn::step::enemy::hothead
