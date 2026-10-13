#include "scn/step/enemy/whispyapple/StateBound2.h"

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
#include "scn/step/enemy/whispyapple/ParamData.h"
#include "scn/step/enemy/whispyapple/StateBoundNear.h"
#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

StateBound2::StateBound2(Enemy* enemy, u32 count, bool flag) : StateBase(enemy), mRot(0.0f), mCount(count), mFlag(flag) {
    obj().footState().setAir();
    const ParamData& param = obj().param().whispyapple();
    f32 speedH = param.mBound2SpeedH * obj().target().getSign();
    obj().move().setSpeedH(speedH);
    obj().move().setSpeedV(param.mBound2SpeedV);
    mRot = obj().model().rotCtrl().getRotV();
}

StateBound2::~StateBound2() {}

void StateBound2::procAnim() {
    const ParamData& param = obj().param().whispyapple();
    mRot += param.mBound2RotSpeed * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    obj().model().rotCtrl().initRotV(mRot);
}

void StateBound2::procMove() {
    const ParamData& param = obj().param().whispyapple();
    obj().move().airDecelFall(param.mDecel, param.mBound2Fall);
}

void StateBound2::procFixPos() {
    const ParamData& param = obj().param().whispyapple();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWall()) {
        WhispyAppleUtility::ReqBoundSE(obj());
        obj().stateChanger().setNextState<StateBoundNear, Enemy*, bool>(objPtr(), mFlag);
    } else if (result.mIsHitFloor) {
        WhispyAppleUtility::ReqBoundSEIfGordo(obj());
        if (mCount != 0) {
            mCount--;
            obj().move().setSpeedV(param.mBound2SpeedV);
        } else {
            obj().stateChanger().setNextState<StateBoundNear, Enemy*, bool>(objPtr(), mFlag);
        }
    }
}

}
}
}
}
