#include "scn/step/enemy/bladeknight/StateDoubleAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/bladeknight/ParamData.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

StateDoubleAttack::StateDoubleAttack(Enemy* enemy) : StateBase(enemy), mFrame(0), mStopCount(0) {
    obj().footState().setGround();
    obj().model().reqScript(8);
}

StateDoubleAttack::~StateDoubleAttack() {}

void StateDoubleAttack::procAnim() {
    const ParamData& param = obj().param().bladeknight();
    if (mStopCount != 0) {
        mStopCount--;
        if (mStopCount == 0) {
            obj().model().anim().setFrameRate(1.0f);
        }
        return;
    }
    if (param.mDoubleAttackStopFrame == obj().model().anim().frame()) {
        obj().model().anim().setFrameRate(0.0f);
        mStopCount = param.mDoubleAttackStopCount;
    }
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateDoubleAttack::procMove() {
    const ParamData& param = obj().param().bladeknight();
    if (mFrame == param.mDoubleAttackMoveFrame1) {
        f32 speed = param.mDoubleAttackSpeed * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    if (mFrame == param.mDoubleAttackMoveFrame2) {
        f32 speed = param.mDoubleAttackSpeed * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    obj().move().groundDecel(obj().param().common().mDecel);
}

void StateDoubleAttack::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
    if (obj().cliffChecker().isCliff()) {
        obj().move().resetSpeedH();
    }
}

}}}}  // namespace scn::step::enemy::bladeknight
