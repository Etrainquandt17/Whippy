#include "scn/step/enemy/sisterbound/BrainWait.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sisterbound/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().move().resetSpeedH();
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

bool BrainWait::onRecover() {
    obj().move().resetVelocity();
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::sisterbound
