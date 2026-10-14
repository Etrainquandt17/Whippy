#include "scn/step/boss/fattybuffer/StateJumpStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateJumpStart::StateJumpStart(Boss* boss, f32 speedH, f32 speedV) : StateBase(boss), mSpeedH(speedH), mSpeedV(speedV) {
    obj().footState().setGround();
    obj().model().reqScript(8);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
}

StateJumpStart::~StateJumpStart() {}

void StateJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateJump, Boss*, f32, f32>(objPtr(), mSpeedH, mSpeedV);
    }
}

void StateJumpStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
