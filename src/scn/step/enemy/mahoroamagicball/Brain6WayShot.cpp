#include "scn/step/enemy/mahoroamagicball/Brain6WayShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/State6WayFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

Brain6WayShot::Brain6WayShot(Enemy& enemy) : BrainBase(enemy) {}

bool Brain6WayShot::onStart() {
    obj().stateChanger().setNextState<State6WayFollow, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
