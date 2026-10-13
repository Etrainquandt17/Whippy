#include "scn/step/enemy/common/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::common
