#include "scn/step/enemy/waddledoo/BrainWalkAround.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateWalkAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

BrainWalkAround::BrainWalkAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkAround::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkAround, Enemy*>(&obj());
    return true;
}

void BrainWalkAround::update() {
    Utility::ChkNururiTurn(obj());
    Utility::ChkCliffTurn(obj());
}

}
}
}
}
