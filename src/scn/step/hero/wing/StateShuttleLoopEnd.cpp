#include "scn/step/hero/wing/StateShuttleLoopEnd.h"
#include "gobj/FootState.h"
#include "gobj/GearAnim.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/WingParam.h"
#include "scn/step/hero/wing/StateFlight.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

StateShuttleLoopEnd::StateShuttleLoopEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0x156);
    const WingParam& param = obj().param().wing();
    obj().invincible().set(param._D0);
    hel::math::Vector3 velocity = obj().move().velocity();
    velocity.y = obj().param().wing()._D4;
    obj().move().setVelocity(velocity);
}

StateShuttleLoopEnd::~StateShuttleLoopEnd() {
    if (obj().model().hat().isValid()) {
        obj().model().hat().anim().start(0x18, false);
    }
}

void StateShuttleLoopEnd::procAnim() {
    if (StateFlight::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateShuttleLoopEnd::procMove() {
    if (obj().footState().isGround()) {
        obj().move().groundDecel(obj().param().common()._2C);
    } else {
        obj().move().airAccelFall(obj().target().isRightDir(), obj().param().wing()._D8, obj().param().common()._90);
    }
}

void StateShuttleLoopEnd::procFixPos() {
}

}
}
}
}
