#include "scn/step/enemy/mahoroamagicball/BrainNWayShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateNWayFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainNWayShot::BrainNWayShot(Enemy& enemy, bool _1) : BrainBase(enemy), _8(_1) {}

bool BrainNWayShot::onStart() {
    obj().stateChanger().setNextState<StateNWayFollow, Enemy*, bool>(&obj(), _8);
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
