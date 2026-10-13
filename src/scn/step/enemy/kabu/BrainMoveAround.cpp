#include "scn/step/enemy/kabu/BrainMoveAround.h"

#include "gobj/Move.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/kabu/StateFall.h"
#include "scn/step/enemy/kabu/StateMoveAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

BrainMoveAround::BrainMoveAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMoveAround::onStart() {
    obj().move().resetSpeedH();
    obj().stateChanger().setNextState<StateMoveAround, Enemy*>(&obj());
    return true;
}

bool BrainMoveAround::onRecover() {
    obj().move().resetSpeedH();
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::kabu
