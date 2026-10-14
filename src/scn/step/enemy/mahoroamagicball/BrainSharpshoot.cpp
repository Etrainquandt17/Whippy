#include "scn/step/enemy/mahoroamagicball/BrainSharpshoot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateSharpshootFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainSharpshoot::BrainSharpshoot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainSharpshoot::onStart() {
    obj().stateChanger().setNextState<StateSharpshootFollow, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
