#include "scn/step/enemy/chilly/StateMove.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/chilly/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

StateMove::StateMove(Enemy* enemy) : StateBase(enemy), mFrame(0), mTurnWait(0) {
    const ParamData& param = obj().param().chilly();
    obj().footState().setGround();
    bool isRight = Utility::IsNearestPlayerRight(obj());
    isRight = app::Random::RandU32(100) > param.mMoveReversePercent ? isRight : !isRight;
    if (isRight != obj().target().isRightDir()) {
        mTurnWait = param.mMoveTurnFrame;
        obj().model().reqScript(0);
        obj().target().setIsRightDir(isRight);
    } else {
        obj().model().reqScript(7);
    }
}

void StateMove::procAnim() {
    if (mTurnWait != 0) {
        mTurnWait--;
    } else {
        mFrame++;
    }
    if (mTurnWait == 1) {
        obj().model().reqScript(7);
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateMove::procMove() {
    const ParamData& param = obj().param().chilly();
    if (mTurnWait == 0 && !obj().cliffChecker().isCliff()) {
        hel::math::Vector3 pos = obj().location().pos();
        if (mFrame > param.mMoveStartFrame) {
            int total = obj().model().anim().totalFrame();
            pos.x += param.mMoveDistance * (2.0f * ((total - (mFrame - param.mMoveStartFrame)) * obj().target().getSign())) / total / total;
        }
        obj().location().setPos(pos);
    }
}

void StateMove::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
