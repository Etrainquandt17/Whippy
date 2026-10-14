#include "scn/step/boss/fattybuffer/StateSwellBackJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellBackJumpLanding.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellBackJump::StateSwellBackJump(Boss* boss, f32 speedH, f32 speedV) : StateBase(boss) {
    obj().footState().setAir();
    obj().model().reqScript(0x16);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().move().setSpeedH(speedH * obj().target().getSign());
    obj().move().setSpeedV(speedV);
}

StateSwellBackJump::~StateSwellBackJump() {}

void StateSwellBackJump::procAnim() {}

void StateSwellBackJump::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().airDecelFall(param._18, param._1C);
}

void StateSwellBackJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateSwellBackJumpLanding, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
