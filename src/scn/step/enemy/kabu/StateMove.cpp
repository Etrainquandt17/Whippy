#include "scn/step/enemy/kabu/StateMove.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/kabu/ParamData.h"
#include "scn/step/enemy/kabu/StateFall.h"
#include "scn/step/enemy/kabu/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

StateMove::StateMove(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mTurnFrame(0), mJumpFrame(0), mIsCliffTurn(false), mIsTurning(false) {
    const ParamData& param = obj().param().kabu();
    obj().footState().setGround();
    if (obj().model().anim().currentG3DAnimIndex() != 8) {
        obj().model().reqScript(9);
    }
    f32 rate = param.mMoveFrameRate;
    if (obj().variation() == 0x68) {
        rate = param.mMoveFrameRateJump;
    }
    obj().model().setFrameRate(rate);
    if (obj().variation() == 0x5F || obj().variation() == 0x67 || obj().variation() == 0x68 || obj().variation() == 0x169) {
        mIsCliffTurn = true;
    }
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
    int rand = app::Random::Rand(0, 4);
    mJumpFrame = param.mMoveJumpFrame + rand * param.mMoveJumpFrameStep;
}

StateMove::~StateMove() {}

void StateMove::procAnim() {
    if (obj().variation() == 0x68) {
        mFrame++;
        if (mFrame == mJumpFrame) {
            obj().stateChanger().setNextState<StateJump, Enemy*>(objPtr());
        }
    }
}

void StateMove::procMove() {
    if (mIsTurning) {
        if (++mTurnFrame == obj().param().kabu().mTurnWaitFrame) {
            mIsTurning = false;
        }
    } else {
        mTurnFrame = 0;
        obj().move().groundAccel(obj().target().isRightDir(), mAccel);
    }
}

void StateMove::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result._2 || Utility::ChkNururiByDir(obj(), 0.1f) || (mIsCliffTurn && obj().cliffChecker().isCliff())) {
        obj().move().resetSpeedH();
        obj().target().setIsRightDir(!obj().target().isRightDir());
        mIsTurning = true;
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
