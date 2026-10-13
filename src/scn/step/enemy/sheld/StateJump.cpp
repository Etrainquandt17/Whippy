#include "scn/step/enemy/sheld/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFallNoDecel.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().move().setSpeedV(obj().param().sheld().mJumpSpeedV);
    f32 speed = 1.0f;
    if (custom.isNuru()) {
        speed = 2.0f;
    }
    custom.resetNuru();
    speed = obj().param().sheld().mJumpSpeedH * (obj().target().isRightDir() ? speed : -speed);
    obj().move().setSpeedH(speed);
    obj().nururi().setValid(false);
}

StateJump::~StateJump() {
    obj().nururi().setValid(true);
}

void StateJump::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFallNoDecel, Enemy*>(objPtr());
    }
}

void StateJump::procMove() {
    obj().move().airDecelFall(obj().param().sheld().mFallDecel, obj().param().sheld().mFall);
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        if (obj().model().anim().frame() >= 1.0f) {
            obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
        }
    }
}

}
}
}
}
