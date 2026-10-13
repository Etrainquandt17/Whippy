#include "scn/step/enemy/common/StateFly.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mCount(0) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
}

StateFly::~StateFly() {}

void StateFly::procAnim() {}

void StateFly::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.02f);
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Create(0.0f, 0.0f, 0.02f);
    obj().move().airDecelFall(decel, fall);
    if (Utility::IsPlayerExist(obj())) {
        hel::math::Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
        bool isRight = playerPos.x > obj().location().pos().x;
        if (isRight != obj().target().isRightDir()) {
            mCount++;
            if (mCount == 30) {
                obj().target().setIsRightDir(isRight);
            }
        } else {
            mCount = 0;
        }
    }
}

void StateFly::procFixPos() {}

}
}
}
}
