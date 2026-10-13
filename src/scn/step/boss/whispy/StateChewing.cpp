#include "scn/step/boss/whispy/StateChewing.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/whispy/CaptureCtrl.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/boss/whispy/StateVomit.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateChewing::StateChewing(Boss* boss) : StateBase(boss), mCount(obj().param().whispy().mChewingCount), mIsFirst(true) {
    obj().model().reqScript(19);
}

StateChewing::~StateChewing() {}

void StateChewing::procAnim() {
    const Param& param = obj().param().whispy();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        u32 damage = mIsFirst ? param.mChewingDamageFirst : param.mChewingDamage;
        custom.captureCtrl().setDamage(damage);
        mIsFirst = false;
    }
    if (obj().model().isAllEnd()) {
        if (mCount != 0) {
            mCount--;
        }
        if (mCount == 0 || custom.captureCtrl().getResistPower() > param.mChewingResistPower) {
            obj().stateChanger().setNextState<StateVomit, Boss*, bool>(objPtr(), mCount != 0);
        } else {
            obj().model().reqScript(19);
        }
    }
}

void StateChewing::procMove() {}

void StateChewing::procFixPos() {}

}
}
}
}
