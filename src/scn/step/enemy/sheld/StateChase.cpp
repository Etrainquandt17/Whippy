#include "scn/step/enemy/sheld/StateChase.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/ParamData.h"
#include "scn/step/enemy/sheld/StateFall.h"
#include "scn/step/enemy/sheld/StateJumpStart.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

StateChase::StateChase(Enemy* enemy) : StateBase(enemy), mAccel(0.0f), mAccelMax(0.0f) {
    const ParamData& param = obj().param().sheld();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        mAccel = param.mDashAccel[0];
        mAccelMax = param.mChaseAccelMax[0];
        break;
    case 1:
        mAccel = param.mDashAccel[1];
        mAccelMax = param.mChaseAccelMax[1];
        break;
    default:
        mAccel = param.mDashAccel[2];
        mAccelMax = param.mChaseAccelMax[2];
        break;
    }
    obj().footState().setGround();
    obj().model().reqScript(9);
    obj().model().anim().setFrameRate(param.mDashFrameRate * mAccel);
    hel::math::Vector2 diff = Utility::GetNearestPlayerPos(obj()) - obj().location().pos().getXY();
    bool isRight = !(diff.x < 0.0f);
    obj().target().setIsRightDir(isRight);
    obj().move().setSpeedH(0.5f * (mAccel * obj().target().getSign()));
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).resetNuru();
    obj().brainCtrl().toValid();
}

StateChase::~StateChase() {}

void StateChase::procAnim() {}

void StateChase::procMove() {
    obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(mAccel, mAccelMax, 0.001f));
}

void StateChase::procFixPos() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().mapColl().result()._2) {
        custom.resetNuru();
        obj().stateChanger().setNextState<StateJumpStart, Enemy*>(objPtr());
        return;
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
        return;
    }
    hel::math::Vector2 dir = obj().nururi().getNururiDir();
    if (hel::math::Math::Abs(dir.x) < 0.1f) {
        hel::math::Vector2 diff = Utility::GetNearestPlayerPos(obj()) - obj().location().pos().getXY();
        bool isRight = !(diff.x < 0.0f);
        obj().target().setIsRightDir(isRight);
    } else {
        custom.setNuru();
        obj().stateChanger().setNextState<StateJumpStart, Enemy*>(objPtr());
    }
}

}
}
}
}
