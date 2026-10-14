#include "scn/step/enemy/stareffect/BrainBound.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/stareffect/StateBound.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

BrainBound::BrainBound(Enemy& enemy) : BrainBase(enemy) {}

bool BrainBound::onStart() {
    obj().stateChanger().setNextState<StateBound, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::stareffect
