#include "scn/step/enemy/mahoroadead/BrainDead.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroadead/StateDead.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroadead {

BrainDead::BrainDead(Enemy& enemy) : BrainBase(enemy) {}

bool BrainDead::onStart() {
    obj().stateChanger().setNextState<StateDead, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroadead
