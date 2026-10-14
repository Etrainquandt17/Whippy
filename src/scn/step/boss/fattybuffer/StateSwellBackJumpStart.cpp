#include "scn/step/boss/fattybuffer/StateSwellBackJumpStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellBackJump.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellBackJumpStart::StateSwellBackJumpStart(Boss* boss, f32 speedH, f32 speedV) : StateBase(boss), mSpeedH(speedH), mSpeedV(speedV) {
    obj().footState().setGround();
    obj().model().reqScript(0x15);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_4);
}

StateSwellBackJumpStart::~StateSwellBackJumpStart() {}

void StateSwellBackJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwellBackJump, Boss*, f32, f32>(objPtr(), mSpeedH, mSpeedV);
    }
}

void StateSwellBackJumpStart::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellBackJumpStart::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
