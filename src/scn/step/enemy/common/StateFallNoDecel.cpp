#include "scn/step/enemy/common/StateFallNoDecel.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/common/StateLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateFallNoDecel::StateFallNoDecel(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
}

StateFallNoDecel::~StateFallNoDecel() {}

void StateFallNoDecel::procAnim() {}

void StateFallNoDecel::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.15f, 0.006f, 0.005f);
    obj().move().airDecelFall(decel, fall);
}

void StateFallNoDecel::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::common
