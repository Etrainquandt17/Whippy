#include "scn/step/boss/lowper/StateSummonBarrier.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateSummonBarrier::StateSummonBarrier(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x15);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
}

StateSummonBarrier::~StateSummonBarrier() {}

void StateSummonBarrier::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyCtrl().requestBarrier();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSummonBarrier::procMove() {}

void StateSummonBarrier::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
