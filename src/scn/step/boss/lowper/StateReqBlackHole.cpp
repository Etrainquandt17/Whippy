#include "scn/step/boss/lowper/StateReqBlackHole.h"

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

StateReqBlackHole::StateReqBlackHole(Boss* boss, u32 kind) : StateBase(boss), mKind(kind) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().model().reqScript(0x28);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.1f);
    custom.miniBlackHoleCtrl().clear();
}

StateReqBlackHole::~StateReqBlackHole() {}

void StateReqBlackHole::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        reqHole();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateReqBlackHole::procMove() {}

void StateReqBlackHole::procFixPos() {}

void StateReqBlackHole::reqHole() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).miniBlackHoleCtrl().set(mKind, 0.0f, 0.00032f, 0.032f);
}

}}}}  // namespace scn::step::boss::lowper
