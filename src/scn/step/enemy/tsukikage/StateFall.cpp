#include "scn/step/enemy/tsukikage/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/tsukikage/ParamData.h"
#include "scn/step/enemy/tsukikage/StateLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(1);
}

StateFall::~StateFall() {}

void StateFall::procMove() {
    obj().move().airDecelFall(obj().param().tsukikage().mFallDecel, obj().param().tsukikage().mFall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::tsukikage
