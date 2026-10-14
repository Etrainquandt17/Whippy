#include "scn/step/enemy/mahoroamagicball/BrainHomingShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateHomingFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainHomingShot::BrainHomingShot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainHomingShot::onStart() {
    obj().stateChanger().setNextState<StateHomingFollow, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
