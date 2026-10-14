#include "scn/step/boss/doubter/StateEtherJumpRise.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateEtherJumpHold.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateEtherJumpRise::StateEtherJumpRise(Boss* boss, u32 frame) : StateBase(boss), mFrame(frame) {
    obj().footState().setAir();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(33);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
    obj().move().resetVelocity();
    obj().move().setSpeedV(obj().param().doubter()._154);
}

StateEtherJumpRise::~StateEtherJumpRise() {}

void StateEtherJumpRise::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateEtherJumpRise::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().airDecelFall(param._15C, param._160);
}

void StateEtherJumpRise::procFixPos() {
    const Param& param = obj().param().doubter();
    f32 height = param._158 + obj().basePos().y;
    if (obj().location().pos().y > height) {
        obj().stateChanger().setNextState<StateEtherJumpHold, Boss*, u32>(objPtr(), mFrame);
    }
}

}}}}  // namespace scn::step::boss::doubter
