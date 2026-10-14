#include "scn/step/boss/watergalboros/StateVomit.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/watergalboros/Custom.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

StateVomit::StateVomit(Boss* boss, bool isSoft) : StateBase(boss), mIsSoft(isSoft) {
    obj().model().reqScript(0x13);
}

StateVomit::~StateVomit() {}

void StateVomit::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        if (mIsSoft) {
            custom.captureCtrl().vomitSoft();
        } else {
            custom.captureCtrl().vomit();
        }
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateVomit::procMove() {}

void StateVomit::procFixPos() {}

}}}}  // namespace scn::step::boss::watergalboros
