#include "scn/step/enemy/grandlowperbullet/BrainShot.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/grandlowperbullet/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

BrainShot::BrainShot(Enemy& enemy) : BrainBase(enemy) {}

bool BrainShot::onStart() {
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
