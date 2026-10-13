#include "scn/step/enemy/waddledee/StateWait.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateWait::StateWait(Enemy* enemy) : StateBase(enemy), mLoopCount(0), mLoopLimit(0), mIsLoop(false) {
    obj().footState().setGround();
    if (obj().variation() == 0x119) {
        int rand = app::Random::Rand(10);
        if (0 <= rand && rand <= 4) {
            obj().model().reqScript(0);
        } else if (5 <= rand && rand <= 6) {
            obj().model().reqScript(31);
        } else {
            obj().model().reqScript(0);
            mIsLoop = true;
            setLoopLimit();
        }
    } else if (obj().variation() == 0x13D) {
        obj().model().reqScript(31);
    } else if (obj().variation() == 0x13C || obj().variation() == 0x145) {
        obj().model().reqScript(0);
        mIsLoop = true;
        setLoopLimit();
    }
    obj().brainCtrl().toValid();
}

void StateWait::procAnim() {
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (mIsLoop) {
        if (obj().model().anim().isLooped() && index == 0) {
            mLoopCount++;
            if (mLoopCount == mLoopLimit) {
                obj().model().reqScript(32);
            }
        } else if (obj().model().isAllEnd() && index == 26) {
            obj().model().reqScript(0);
            mLoopCount = 0;
            setLoopLimit();
        }
    }
}

void StateWait::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

void StateWait::setLoopLimit() {
    switch (app::Random::Rand(3)) {
    case 0:
        mLoopLimit = 1;
        break;
    case 1:
        mLoopLimit = 2;
        break;
    case 2:
        mLoopLimit = 3;
        break;
    }
}

}}}}  // namespace scn::step::enemy::waddledee
