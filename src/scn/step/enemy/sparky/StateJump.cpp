#include "scn/step/enemy/sparky/StateJump.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/sparky/ParamData.h"

using app::Random;

namespace scn {
namespace step {
namespace enemy {
namespace sparky {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(8);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    const ParamData& param = obj().param().sparky();
    if (obj().model().isAllEnd()) {
        if (obj().model().anim().currentG3DAnimIndex() == 6) {
            obj().footState().setAir();
            obj().model().reqScript(7);
            if (Random::Rand(param.mHighJumpRate) == 0) {
                obj().move().setSpeedV(param.mJumpSpeedLow);
            } else {
                obj().move().setSpeedV(param.mJumpSpeedHigh);
            }
            if (obj().variation() == 0x22) {
                obj().move().setSpeedH(param.mJumpSpeedH * obj().target().getSign());
            }
        } else if (obj().model().anim().currentG3DAnimIndex() == 5) {
            obj().model().reqScript(1);
        }
    }
}

void StateJump::procMove() {
    if (obj().footState().isAir()) {
        const ParamData& param = obj().param().sparky();
        obj().move().airDecelFall(obj().param().sparky().mDecel, param.mFall);
    }
}

void StateJump::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor && obj().footState().isGround()) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    } else if (obj().mapColl().result().mIsHitFloor && obj().model().anim().currentG3DAnimIndex() == 1) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::sparky
