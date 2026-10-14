#include "scn/step/enemy/walky/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateFallNoDecel.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/walky/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFallNoDecel, Enemy*>(objPtr());
    }
    if (mFrame == obj().param().walky().mJumpFrame) {
        obj().footState().setAir();
        obj().move().setSpeedH(obj().param().walky().mJumpSpeedH * obj().target().getSign());
        obj().move().setSpeedV(obj().param().walky().mJumpSpeedV);
        obj().soundSE().start(0x2a7);
    }
}

void StateJump::procMove() {
    if (obj().footState().isAir()) {
        obj().move().airDecelFall(obj().param().walky().mJumpDecel, obj().param().walky().mJumpFall);
    }
}

void StateJump::procFixPos() {
    if (obj().footState().isAir()) {
        if (obj().mapColl().result().mIsHitFloor) {
            obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
        }
    } else if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::walky
