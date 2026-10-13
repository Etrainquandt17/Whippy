#include "scn/step/enemy/kabu/BrainMoveStraight.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/kabu/StateFall.h"
#include "scn/step/enemy/kabu/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

BrainMoveStraight::BrainMoveStraight(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMoveStraight::onStart() {
    Utility::SetTargetByDirType(obj());
    obj().stateChanger().setNextState<StateMove, Enemy*>(&obj());
    return true;
}

bool BrainMoveStraight::onRecover() {
    obj().move().resetSpeedH();
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::kabu
