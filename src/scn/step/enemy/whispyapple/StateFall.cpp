#include "scn/step/enemy/whispyapple/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/whispyapple/ParamData.h"
#include "scn/step/enemy/whispyapple/StateBound1.h"
#include "scn/step/enemy/whispyapple/StateBound2.h"
#include "scn/step/enemy/whispyapple/StateBoundNear.h"
#include "scn/step/enemy/whispyapple/WhispyAppleUtility.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

StateFall::StateFall(Enemy* enemy, u32 count, bool flag) : StateBase(enemy), mFallSpeed(0.0f), mCount(count), mFlag(flag) {
    obj().footState().setAir();
    obj().move().resetVelocity();
    obj().model().reqScript(0);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {}

void StateFall::procMove() {
    const ParamData& param = obj().param().whispyapple();
    mFallSpeed += param.mFallAccel;
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(param.mFallResist, mFallSpeed, 0.0f);
    obj().move().airDecelFall(param.mDecel, fall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().isHit()) {
        Utility::TurnHero(obj());
        WhispyAppleUtility::ReqBoundSE(obj());
        if (mCount == 0) {
            obj().stateChanger().setNextState<StateBoundNear, Enemy*, bool>(objPtr(), mFlag);
        } else {
            mCount--;
            if (obj().kind() == 0xa) {
                obj().stateChanger().setNextState<StateBound2, Enemy*, u32, bool>(objPtr(), mCount, mFlag);
            } else {
                obj().stateChanger().setNextState<StateBound1, Enemy*, u32, bool>(objPtr(), mCount, mFlag);
            }
        }
    }
}

}}}}  // namespace scn::step::enemy::whispyapple
