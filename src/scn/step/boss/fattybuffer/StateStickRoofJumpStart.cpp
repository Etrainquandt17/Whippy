#include "scn/step/boss/fattybuffer/StateStickRoofJumpStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateStickRoofJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStickRoofJumpStart::StateStickRoofJumpStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0xB);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateStickRoofJumpStart::~StateStickRoofJumpStart() {}

void StateStickRoofJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateStickRoofJump, Boss*>(objPtr());
    }
}

void StateStickRoofJumpStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateStickRoofJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
