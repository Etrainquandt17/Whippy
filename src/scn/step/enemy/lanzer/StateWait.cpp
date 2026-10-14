#include "scn/step/enemy/lanzer/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().model().setFrameRate(0.25f);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::lanzer
