#include "scn/step/enemy/leafan/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/leafan/ParamData.h"
#include "scn/step/enemy/leafan/StateFall.h"
#include "scn/step/enemy/leafan/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace leafan {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    f32 speed = obj().param().leafan().mJumpSpeed;
    obj().move().setSpeedV(speed);
    obj().soundSE().start(0x2b8);
}

void StateJump::procAnim() {
    if (obj().move().velocity().y <= 0.0) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateJump::procMove() {
    obj().move().airAccelFall(obj().target().isRightDir(), obj().param().leafan().mJumpAccel, obj().param().leafan().mJumpFall);
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && obj().model().anim().frame() >= 1.0f) {
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::leafan
