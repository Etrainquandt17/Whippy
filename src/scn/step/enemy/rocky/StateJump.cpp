#include "scn/step/enemy/rocky/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/Custom.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().move().setSpeedV(obj().param().rocky().mJumpSpeedV);
    obj().move().setSpeedH(obj().param().rocky().mJumpSpeedH * obj().target().getSign());
    obj().soundSE().start(0x2a7);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    mFrame++;
    if (mFrame == obj().param().rocky().mJumpStopFrame) {
        obj().move().resetSpeedH();
        obj().move().resetSpeedV();
    } else if (mFrame == obj().param().rocky().mJumpStopFrame + obj().param().rocky().mJumpFallFrame) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).setFallSpeedUp(true);
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateJump::procMove() {
    if (mFrame < obj().param().rocky().mJumpStopFrame) {
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), obj().param().rocky().mJumpFall);
    }
}

void StateJump::procFixPos() {}

}}}}  // namespace scn::step::enemy::rocky
