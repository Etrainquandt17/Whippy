#include "scn/step/enemy/blipper/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/blipper/ParamData.h"
#include "scn/step/enemy/blipper/StateFall.h"
#include "scn/step/enemy/blipper/StateJump.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(2);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        if (obj().variation() == 0x170) {
            obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
        }
    }
}

void StateLanding::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
