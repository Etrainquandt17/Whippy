#include "scn/step/enemy/strikeboxbullet/BrainShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/strikeboxbullet/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace strikeboxbullet {

BrainShot::BrainShot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainShot::onStart() {
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::strikeboxbullet
