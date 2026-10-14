#include "scn/step/enemy/mahoroamagicball/BrainDemo.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateDemoFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainDemo::BrainDemo(Enemy& enemy) : BrainBase(enemy) {}

bool BrainDemo::onStart() {
    obj().stateChanger().setNextState<StateDemoFollow, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
