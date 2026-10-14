#include "scn/step/boss/moundeath/StateRollingStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/moundeath/Custom.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/StateRolling.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateRollingStart::StateRollingStart(Boss* boss) : StateBase(boss), mCount(0), mRot(0.0f), mRotDiff(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x18);
    Utility::ControlHateOnAction(obj());
    Utility::TurnHatedHero(obj());
    obj().guard().setType(static_cast<GuardType>(6));
    custom.setBodyCollRolling();
    mRot = obj().model().rotCtrl().getRotH() * obj().target().getSign();
    mRotDiff = chara::ModelRotCtrl::ROT_H_TARGET - mRot;
    obj().soundSE().normal().start(0x5A6);
}

StateRollingStart::~StateRollingStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateRollingStart::procAnim() {
    const Param& param = obj().param().moundeath();
    mCount++;
    f32 delta = (360.0f * static_cast<f32>(param._100) + mRotDiff) / static_cast<f32>(param._FC);
    mRot = obj().model().rotCtrl().calcChangedRot(mRot, true, delta);
    obj().model().rotCtrl().initRotH(mRot);
    if (mCount == param._FC) {
        obj().stateChanger().setNextState<StateRolling, Boss*>(objPtr());
    }
}

void StateRollingStart::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().groundAccel(!obj().target().isRightDir(), param._104);
}

void StateRollingStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::moundeath
