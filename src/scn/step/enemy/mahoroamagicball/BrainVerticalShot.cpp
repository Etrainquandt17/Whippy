#include "scn/step/enemy/mahoroamagicball/BrainVerticalShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateVerticalShotFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainVerticalShot::BrainVerticalShot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainVerticalShot::onStart() {
    obj().stateChanger().setNextState<StateVerticalShotFollow, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
