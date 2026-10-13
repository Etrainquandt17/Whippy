#include "scn/step/enemy/waddledoo/BrainWalkStraight.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

BrainWalkStraight::BrainWalkStraight(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkStraight::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

void BrainWalkStraight::update() {
    Utility::ChkNururiTurn(obj());
    Utility::ChkCliffTurn(obj());
}

}
}
}
}
