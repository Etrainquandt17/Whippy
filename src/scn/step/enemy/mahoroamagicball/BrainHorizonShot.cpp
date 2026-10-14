#include "scn/step/enemy/mahoroamagicball/BrainHorizonShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateHorizonShotFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainHorizonShot::BrainHorizonShot(Enemy& enemy, bool _1) : BrainBase(enemy), _8(_1) {}

bool BrainHorizonShot::onStart() {
    obj().stateChanger().setNextState<StateHorizonShotFollow, Enemy*, bool>(&obj(), _8);
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
