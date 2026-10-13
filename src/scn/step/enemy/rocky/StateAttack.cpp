#include "scn/step/enemy/rocky/StateAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/enemy/rocky/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    bool isOtherAnim = static_cast<u32>(obj().model().anim().currentG3DAnimIndex()) != 3;
    obj().footState().setGround();
    obj().model().reqScript(9);
    obj().model().anim().setFrameRate(1.0f);
    if (isOtherAnim) {
        obj().model().anim().setFrameToTail();
    }
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
}

StateAttack::~StateAttack() {}

void StateAttack::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd() && mFrame > obj().param().rocky().mAttackWait) {
        obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
    }
}

void StateAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
