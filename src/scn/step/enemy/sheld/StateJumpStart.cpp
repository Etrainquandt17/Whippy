#include "scn/step/enemy/sheld/StateJumpStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/ParamData.h"
#include "scn/step/enemy/sheld/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateJumpStart::StateJumpStart(Enemy* enemy) : StateBase(enemy), mWait(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
    custom.setPos();
    if (custom.isNuru()) {
        mWait = 1;
    } else {
        mWait = obj().param().sheld().mJumpStartWait;
    }
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    if (mWait == 0) {
        if (obj().model().isAllEnd()) {
            obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(0.05f, 0.001f, 0.001f));
            obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
        }
    } else {
        mWait--;
        if (mWait == 0) {
            obj().model().reqScript(8);
        }
    }
}

void StateJumpStart::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).resetNuru();
    }
}

}
}
}
}
