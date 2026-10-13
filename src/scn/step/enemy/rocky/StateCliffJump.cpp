#include "scn/step/enemy/rocky/StateCliffJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/rocky/Custom.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateCliffJump::StateCliffJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(1);
    obj().move().setSpeedV(obj().param().rocky().mCliffJumpSpeedV);
    obj().move().setSpeedH(obj().param().rocky().mCliffJumpSpeedH * obj().target().getSign());
    obj().soundSE().start(0x2a7);
}

StateCliffJump::~StateCliffJump() {}

void StateCliffJump::procAnim() {
    mFrame++;
    if (mFrame == obj().param().rocky().mCliffJumpStopFrame) {
        obj().move().resetSpeedH();
        obj().move().resetSpeedV();
    } else if (mFrame == obj().param().rocky().mCliffJumpStopFrame + obj().param().rocky().mCliffJumpFallFrame) {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setFallSpeedUp(true);
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateCliffJump::procMove() {
    if (mFrame < obj().param().rocky().mCliffJumpStopFrame) {
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), obj().param().rocky().mCliffJumpFall);
    }
}

void StateCliffJump::procFixPos() {}

}
}
}
}
