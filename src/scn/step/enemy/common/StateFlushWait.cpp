#include "scn/step/enemy/common/StateFlushWait.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateFlush.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateFlushWait::StateFlushWait(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(0);
    Utility::SetTargetByDirType(obj());
}

void StateFlushWait::procFixPos() {
    Utility::TurnHero(obj());
    if (Utility::IsHeroInRange(obj(), 8.0f, -8.0f, -7.5f, 7.5f) || !obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFlush, Enemy*>(objPtr());
    }
}

}
}
}
}
