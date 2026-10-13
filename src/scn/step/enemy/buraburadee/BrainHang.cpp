#include "scn/step/enemy/buraburadee/BrainHang.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/buraburadee/StateHang.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {

BrainHang::BrainHang(Enemy& enemy) : BrainBase(enemy) {}

bool BrainHang::onStart() {
    obj().stateChanger().setNextState<StateHang, Enemy*>(&obj());
    return true;
}

bool BrainHang::onLanding() {
    obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(&obj());
    return true;
}

void BrainHang::update() {
    Utility::ChkNururiTurn(obj());
    Utility::ChkCliffTurn(obj());
}

}
}
}
}
