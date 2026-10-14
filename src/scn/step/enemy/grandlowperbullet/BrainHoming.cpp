#include "scn/step/enemy/grandlowperbullet/BrainHoming.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/grandlowperbullet/StatePrepare.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

BrainHoming::BrainHoming(Enemy& enemy) : BrainBase(enemy) {}

bool BrainHoming::onStart() {
    obj().stateChanger().setNextState<StatePrepare, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
