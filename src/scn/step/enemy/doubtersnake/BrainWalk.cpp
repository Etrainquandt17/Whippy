#include "scn/step/enemy/doubtersnake/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/doubtersnake/StateAppear.h"
#include "scn/step/enemy/doubtersnake/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onLanding() {
    obj().stateChanger().setNextState<StateWalk, Enemy*>(&obj());
    return true;
}

void BrainWalk::update() {
    Utility::ChkNururiTurn(obj());
}

}
}
}
}
