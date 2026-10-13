#include "scn/step/enemy/broomhatter/BrainWalkAround.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/broomhatter/StateWalkAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

BrainWalkAround::BrainWalkAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkAround::onLanding() {
    obj().stateChanger().setNextState<StateWalkAround, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::broomhatter
