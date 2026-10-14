#include "scn/step/boss/fattybuffer/StateSwellStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellWait.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellStart::StateSwellStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0x12);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateSwellStart::~StateSwellStart() {}

void StateSwellStart::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_10);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwellWait, Boss*>(objPtr());
    }
}

void StateSwellStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
