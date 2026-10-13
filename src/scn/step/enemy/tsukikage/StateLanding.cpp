#include "scn/step/enemy/tsukikage/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/tsukikage/StateFall.h"
#include "scn/step/enemy/tsukikage/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(2);
    obj().model().rotCtrl().setValid(false);
}

StateLanding::~StateLanding() {
    obj().model().rotCtrl().setValid(true);
}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
    }
}

void StateLanding::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
