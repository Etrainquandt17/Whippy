#include "scn/step/boss/bonkers/StateSwing.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Custom.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/bonkers/StateSwingEnd.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateSwing::StateSwing(Boss* boss) : StateBase(boss), mIsMove(false), mCount(0) {
    obj().footState().setGround();
    obj().model().reqScript(11);
}

StateSwing::~StateSwing() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateSwing::procAnim() {
    const Param& param = obj().param().bonkers();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < param.mSwingTime) {
        if (mIsMove) {
            mCount++;
        }
    } else {
        obj().stateChanger().setNextState<StateSwingEnd, Boss*>(objPtr());
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
    }
    if (obj().scriptTrigger().get(1)) {
        obj().guard().setType(GUARD_TYPE_6);
        custom.setBodyCollSwing();
    }
}

void StateSwing::procMove() {
    const Param& param = obj().param().bonkers();
    if (mIsMove) {
        obj().move().groundAccel(obj().target().isRightDir(), param.mSwingAccel);
    } else {
        obj().move().groundDecel(param._24);
    }
}

void StateSwing::procFixPos() {
    if (common::StateFall::TryToChangeState(objPtr())) {
        return;
    }
    if (!mIsMove) {
        return;
    }
    if (obj().mapColl().result()._2 || obj().worldCage().isCorrected()) {
        obj().stateChanger().setNextState<StateSwingEnd, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::bonkers
