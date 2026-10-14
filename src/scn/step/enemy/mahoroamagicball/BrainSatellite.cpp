#include "scn/step/enemy/mahoroamagicball/BrainSatellite.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/mahoroamagicball/StateSatellite.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

BrainSatellite::BrainSatellite(Enemy& enemy) : BrainBase(enemy) {}

bool BrainSatellite::onStart() {
    obj().stateChanger().setNextState<StateSatellite, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
