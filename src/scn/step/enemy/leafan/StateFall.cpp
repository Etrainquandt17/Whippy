#include "scn/step/enemy/leafan/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/leafan/ParamData.h"
#include "scn/step/enemy/leafan/StateLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace leafan {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(1);
}

void StateFall::procMove() {
    obj().move().airDecelFall(obj().param().leafan().mDecel, obj().param().leafan().mFall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::leafan
