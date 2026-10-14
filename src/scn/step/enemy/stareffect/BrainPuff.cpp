#include "scn/step/enemy/stareffect/BrainPuff.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/stareffect/StatePuff.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

BrainPuff::BrainPuff(Enemy& enemy) : BrainBase(enemy) {}

bool BrainPuff::onStart() {
    obj().stateChanger().setNextState<StatePuff, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::stareffect
