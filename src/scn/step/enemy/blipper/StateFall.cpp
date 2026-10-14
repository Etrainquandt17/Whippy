#include "scn/step/enemy/blipper/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/blipper/StateLanding.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().model().unsetCustomMtx();
}

void StateFall::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
    }
}

void StateFall::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f));
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::blipper
