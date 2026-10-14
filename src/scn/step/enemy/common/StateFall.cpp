#include "scn/step/enemy/common/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateLanding.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {}

void StateFall::procMove() {
    Vector2 pos = obj().location().centerPos().getXY();
    const gobj::MoveParamFall& fall =
        !Utility::IsWaterGrid(obj(), pos.x, pos.y) ? obj().param().common().mFall : obj().param().common().mFallWater;
    obj().move().airDecelFall(obj().param().common().mDecel, fall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::common
