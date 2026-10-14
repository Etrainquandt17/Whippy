#include "scn/step/enemy/doubtersnake/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/doubtersnake/ParamData.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    const ParamData& param = obj().param().doubtersnake();
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().model().anim().setFrameRate(param.mJumpFrameRate);
    f32 speedH;
    if (obj().level() == 0) {
        speedH = param.mJumpSpeedH;
    } else {
        speedH = param.mJumpSpeedHHard;
    }
    obj().move().setVelocity(Vector3(speedH * obj().target().getSign(), param.mJumpSpeedV, 0.0f));
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(1);
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().doubtersnake();
    obj().move().airDecelFall(param.mJumpDecel, param.mJumpFall);
}

void StateJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHitWall()) {
        obj().move().resetSpeedH();
        obj().target().invert();
    }
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::doubtersnake
