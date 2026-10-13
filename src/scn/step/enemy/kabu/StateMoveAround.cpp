#include "scn/step/enemy/kabu/StateMoveAround.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/kabu/ParamData.h"
#include "scn/step/enemy/kabu/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

StateMoveAround::StateMoveAround(Enemy* enemy)
    : StateBase(enemy), mCenterX(obj().location().pos().x), mTurnFrame(0), mIsTurning(false) {
    const ParamData& param = obj().param().kabu();
    obj().footState().setGround();
    obj().model().reqScript(9);
    obj().model().setFrameRate(param.mMoveFrameRate);
    switch (obj().level()) {
    case 0:
        mAccel = param.mAccelLevel0;
        break;
    case 1:
        mAccel = param.mAccelLevel1;
        break;
    case 2:
        mAccel = param.mAccelLevel2;
        break;
    default:
        mAccel = param.mAccelLevel3;
        break;
    }
    obj().move().setSpeedH(mAccel._0);
}

StateMoveAround::~StateMoveAround() {}

void StateMoveAround::procMove() {
    const ParamData& param = obj().param().kabu();
    if (mIsTurning) {
        mTurnFrame++;
        if (mTurnFrame == param.mTurnWaitFrame) {
            mIsTurning = false;
        }
    } else {
        mTurnFrame = 0;
        obj().move().groundAccel(obj().target().isRightDir(), mAccel);
    }
}

void StateMoveAround::procFixPos() {
    const ParamData& param = obj().param().kabu();
    chara::MapCollResult result = obj().mapColl().result();
    f32 x = obj().location().pos().x;
    if ((x <= mCenterX - param.mMoveAroundRange && !obj().target().isRightDir())
        || (mCenterX + param.mMoveAroundRange <= x && obj().target().isRightDir())) {
        turn();
    } else if (result._2 || obj().cliffChecker().isCliff() || Utility::ChkNururiByDir(obj(), 0.1f)) {
        if (obj().target().isRightDir()) {
            mCenterX = mCenterX - param.mMoveAroundRange;
        } else {
            mCenterX = mCenterX + param.mMoveAroundRange;
        }
        turn();
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().move().resetSpeedH();
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateMoveAround::turn() {
    obj().move().resetSpeedH();
    obj().target().invert();
    mIsTurning = true;
}

}}}}  // namespace scn::step::enemy::kabu
