#include "scn/step/enemy/grandlowperbullet/BrainBomb.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/grandlowperbullet/StateBomb.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

BrainBomb::BrainBomb(Enemy& enemy) : BrainBase(enemy) {}

bool BrainBomb::onStart() {
    obj().stateChanger().setNextState<StateBomb, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
