#include "scn/step/boss/doubter/StateCatch.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateCatch::StateCatch(Boss* boss) : StateBase(boss), mDecel(boss->param().doubter().mPunch._4) {
    const PunchParam& punch = Utility::IsVariationExtra(obj()) ? obj().param().doubter().mPunchExtra : obj().param().doubter().mPunch;
    obj().footState().setGround();
    Utility::ControlHateOnAction(obj());
    obj().move().setSpeedH(punch._0 * obj().target().getSign());
    mDecel = punch._4;
    obj().model().reqScript(19);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(5));
}

StateCatch::~StateCatch() {}

void StateCatch::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(4)) {
        custom.punchCtrlR().catchEnd();
    }
    if (obj().scriptTrigger().get(5)) {
        if (custom.captureCtrl().isCapture()) {
            custom.captureCtrl().hide();
        }
        custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateCatch::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(mDecel));
}

void StateCatch::procFixPos() {}

void StateCatch::procObjCollReact() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().checkCapture();
}

}}}}  // namespace scn::step::boss::doubter
