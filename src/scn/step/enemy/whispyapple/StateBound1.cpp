#include "scn/step/enemy/whispyapple/StateBound1.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/whispyapple/ParamData.h"
#include "scn/step/enemy/whispyapple/StateBound2.h"
#include "scn/step/enemy/whispyapple/StateBoundNear.h"
#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

StateBound1::StateBound1(Enemy* enemy, u32 count, bool flag)
    : StateBase(enemy), mFallSpeed(0.0f), mFallAccel(0.0f), mRot(0.0f), mIsRising(true), mCount(count), mFlag(flag) {
    obj().footState().setAir();
    const ParamData& param = obj().param().whispyapple();
    obj().move().setSpeedV(param.mBound1SpeedV);
    mFallAccel = param.mBound1FallAccel;
}

StateBound1::~StateBound1() {}

void StateBound1::procAnim() {
    const ParamData& param = obj().param().whispyapple();
    mRot += param.mBound1RotSpeed * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    obj().model().rotCtrl().initRotV(mRot);
}

void StateBound1::procMove() {
    const ParamData& param = obj().param().whispyapple();
    if (mIsRising) {
        mFallAccel -= param.mBound1FallAccelDecel;
        if (mFallAccel < 0.0f) {
            mFallAccel = 0.0f;
        }
    } else {
        mFallAccel = param.mBound1FallAccelDown;
    }
    mFallSpeed += mFallAccel;
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(param.mBound1FallResist, mFallSpeed, 0.0f);
    obj().move().airAccelFall(obj().target().isRightDir(), param.mBound1Accel, fall);
    if (mIsRising && obj().move().velocity().y < 0.0f) {
        obj().move().resetSpeedV();
        mFallSpeed = param.mBound1FallSpeed;
        mIsRising = false;
    }
}

void StateBound1::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWall()) {
        WhispyAppleUtility::ReqBoundSE(obj());
        obj().stateChanger().setNextState<StateBoundNear, Enemy*, bool>(objPtr(), mFlag);
    } else if (result.mIsHitFloor) {
        WhispyAppleUtility::ReqBoundSE(obj());
        if (mCount != 0) {
            mCount--;
            obj().stateChanger().setNextState<StateBound2, Enemy*, u32, bool>(objPtr(), mCount, mFlag);
        } else {
            obj().stateChanger().setNextState<StateBoundNear, Enemy*, bool>(objPtr(), mFlag);
        }
    }
}

}}}}  // namespace scn::step::enemy::whispyapple
