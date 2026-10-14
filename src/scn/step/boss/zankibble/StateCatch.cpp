#include "scn/step/boss/zankibble/StateCatch.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/zankibble/Custom.h"
#include "scn/step/boss/zankibble/Param.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

StateCatch::StateCatch(Boss* boss) : StateBase(boss), mIsCaught(false) {
    obj().footState().setGround();
    obj().model().reqScript(0);
}

StateCatch::~StateCatch() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyCtrl().isCaught();
}

void StateCatch::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.enemyCtrl().isCaught()) {
        obj().model().reqScript(13);
        obj().soundSE().normal().start(0x595);
        mIsCaught = true;
    }
    if ((mIsCaught && obj().model().isAllEnd()) || (!mIsCaught && !custom.enemyCtrl().isHoldCatchWaitCutter())) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateCatch::procMove() {
    const Param& param = obj().param().zankibble();
    obj().move().groundDecel(param._24);
}

void StateCatch::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::zankibble
