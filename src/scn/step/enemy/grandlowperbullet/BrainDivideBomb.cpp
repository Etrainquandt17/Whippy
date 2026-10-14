#include "scn/step/enemy/grandlowperbullet/BrainDivideBomb.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/grandlowperbullet/StateDivideBomb.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

BrainDivideBomb::BrainDivideBomb(Enemy& enemy) : BrainBase(enemy) {}

bool BrainDivideBomb::onStart() {
    obj().stateChanger().setNextState<StateDivideBomb, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
