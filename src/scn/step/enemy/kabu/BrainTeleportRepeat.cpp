#include "scn/step/enemy/kabu/BrainTeleportRepeat.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/kabu/StateTeleport.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

BrainTeleportRepeat::BrainTeleportRepeat(Enemy& enemy) : BrainBase(enemy) {}

bool BrainTeleportRepeat::onStart() {
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<StateTeleport, Enemy*>(&obj());
    return true;
}

bool BrainTeleportRepeat::onRecover() {
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
    obj().stateChanger().setNextState<StateTeleport, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::kabu
