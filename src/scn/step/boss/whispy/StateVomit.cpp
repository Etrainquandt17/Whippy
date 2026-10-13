#include "scn/step/boss/whispy/StateVomit.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/whispy/CaptureCtrl.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/DamageEyeCtrl.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateVomit::StateVomit(Boss* boss, bool isSoft) : StateBase(boss), mIsSoft(isSoft) {
    obj().model().reqScript(20);
    if (mIsSoft) {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).damageEyeCtrl().set();
    }
}

StateVomit::~StateVomit() {}

void StateVomit::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
        if (mIsSoft) {
            custom.captureCtrl().vomitSoft();
        } else {
            custom.captureCtrl().vomit();
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateVomit::procMove() {}

void StateVomit::procFixPos() {}

}}}}  // namespace scn::step::boss::whispy
