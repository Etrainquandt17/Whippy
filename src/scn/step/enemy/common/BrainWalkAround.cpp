#include "scn/step/enemy/common/BrainWalkAround.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateWalkAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

BrainWalkAround::BrainWalkAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkAround::onLanding() {
    obj().stateChanger().setNextState<StateWalkAround, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::common
