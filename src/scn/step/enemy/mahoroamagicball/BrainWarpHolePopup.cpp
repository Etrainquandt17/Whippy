#include "scn/step/enemy/mahoroamagicball/BrainWarpHolePopup.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateWarpHolePopup.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainWarpHolePopup::BrainWarpHolePopup(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWarpHolePopup::onStart() {
    obj().stateChanger().setNextState<StateWarpHolePopup, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
