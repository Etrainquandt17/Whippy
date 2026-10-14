#include "scn/step/enemy/walky/StateAttackEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/walky/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

StateAttackEnd::StateAttackEnd(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
}

StateAttackEnd::~StateAttackEnd() {}

void StateAttackEnd::procAnim() {
    mFrame++;
    if (mFrame >= obj().param().walky().mAttackEndFrame) {
        obj().brainCtrl().toValid();
    }
}

void StateAttackEnd::procMove() {}

void StateAttackEnd::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::walky
