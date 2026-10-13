#include "scn/step/enemy/hothead/StateAttackBreath.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateWait.h"
#include "scn/step/enemy/common/StateWalkStraight.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

StateAttackBreath::StateAttackBreath(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(7);
}

StateAttackBreath::~StateAttackBreath() {}

void StateAttackBreath::procAnim() {
    if (obj().model().isAllEnd()) {
        if (obj().variation() == 0x11b || obj().variation() == 0x11c) {
            obj().stateChanger().setNextState<common::StateWalkStraight, Enemy*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
        }
    }
}

void StateAttackBreath::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateAttackBreath::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
