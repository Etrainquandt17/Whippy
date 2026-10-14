#include "scn/step/boss/watergalboros/StateCapture.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/watergalboros/Custom.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/boss/watergalboros/StateVomit.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

StateCapture::StateCapture(Boss* boss) : StateBase(boss), mCount(0), mIsFirst(true) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x12);
    custom.captureCtrl().setInvisibility();
}

StateCapture::~StateCapture() {}

void StateCapture::procAnim() {
    const Param& param = obj().param().watergalboros();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.captureCtrl().setDamage(mIsFirst ? param.mCaptureDamageFirst : param.mCaptureDamage);
        mIsFirst = false;
    }
    if (obj().model().isAllEnd()) {
        if (mCount < param.mCaptureCount) {
            mCount++;
        }
        if (mCount == param.mCaptureCount) {
            obj().stateChanger().setNextState<StateVomit, Boss*, bool>(objPtr(), false);
        } else if (custom.captureCtrl().getResistPower() > param.mCaptureResistPower) {
            obj().stateChanger().setNextState<StateVomit, Boss*, bool>(objPtr(), true);
        } else {
            obj().model().reqScript(0x12);
        }
    }
}

void StateCapture::procMove() {}

void StateCapture::procFixPos() {}

}}}}  // namespace scn::step::boss::watergalboros
