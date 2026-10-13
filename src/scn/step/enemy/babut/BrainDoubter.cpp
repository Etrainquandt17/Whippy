#include "scn/step/enemy/babut/BrainDoubter.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/babut/StateDoubterAppear.h"
#include "scn/step/enemy/babut/StateEscape.h"

namespace scn {
namespace step {
namespace enemy {
namespace babut {

BrainDoubter::BrainDoubter(Enemy& enemy) : BrainBase(enemy) {}

bool BrainDoubter::onStart() {
    obj().stateChanger().setNextState<StateDoubterAppear, Enemy*>(&obj());
    return true;
}

bool BrainDoubter::onRecover() {
    obj().stateChanger().setNextState<StateEscape, Enemy*>(&obj());
    return true;
}

}
}
}
}
