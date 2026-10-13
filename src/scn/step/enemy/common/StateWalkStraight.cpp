#include "scn/step/enemy/common/StateWalkStraight.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/CliffChecker.h"
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

StateWalkStraight::StateWalkStraight(Enemy* enemy) : StateBase(enemy) {
    switch (enemy->level()) {
    case 0:
        mAccel = gobj::MoveParamAccel::Create(0.02f, 0.001f, 0.001f);
        break;
    case 1:
        mAccel = gobj::MoveParamAccel::Create(0.03f, 0.002f, 0.001f);
        break;
    case 2:
        mAccel = gobj::MoveParamAccel::Create(0.04f, 0.003f, 0.001f);
        break;
    default:
        mAccel = gobj::MoveParamAccel::Create(0.06f, 0.004f, 0.001f);
        obj().cliffChecker().changeFrontDist(obj().param().common().mCliffFrontDist);
        break;
    }
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().model().setFrameRate(mAccel._0 / 0.02f);
    obj().brainCtrl().toValid();
}

StateWalkStraight::~StateWalkStraight() {}

void StateWalkStraight::procAnim() {}

void StateWalkStraight::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), mAccel);
}

void StateWalkStraight::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result._2) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::common
