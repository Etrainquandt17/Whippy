#include "scn/step/enemy/craby/BrainWalk.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/craby/StateWalkAround.h"
#include "scn/step/enemy/craby/StateWalkStraight.h"

namespace scn {
namespace step {
namespace enemy {
namespace craby {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    switch (obj().variation()) {
    case 0xd0:
    case 0xd1:
        obj().stateChanger().setNextState<StateWalkStraight, Enemy*>(&obj());
        break;
    default:
        obj().stateChanger().setNextState<StateWalkAround, Enemy*>(&obj());
        break;
    }
    return true;
}

bool BrainWalk::onLanding() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::craby
