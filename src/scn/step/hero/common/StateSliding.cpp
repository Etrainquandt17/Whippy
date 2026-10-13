#include "scn/step/hero/common/StateSliding.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateJumpHold.h"
#include "scn/step/hero/common/StateSlidingHit.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateSliding::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isBombDanger()) {
        return false;
    }
    if (hero->vacuumAttacker().vacuumCount() != 0) {
        return false;
    }
    if (hero->mapColl().result().mIsHitFloor && hero->hid().isHold(4) && hero->hid().isTrigger(0x10)) {
        hero->stateChanger().setNextState<StateSliding, Hero*>(hero);
        return true;
    }
    return false;
}

StateSliding::StateSliding(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setGround();
    obj().stateChecker().setSquat(true);
    obj().model().script().start(0xB);
}

StateSliding::~StateSliding() {
    obj().stateChecker().setSquat(false);
}

void StateSliding::procAnim() {
    mFrame++;
    obj().abilityManager().chkDiscardAbility();
    if (mFrame == obj().param().common()._1A8) {
        obj().move().setSpeedH(obj().target().getSign() * obj().param().common()._1A4);
    }
    if (mFrame > obj().param().common()._1A8) {
        if (0.0f == obj().move().velocity().x) {
            obj().stateChanger().setNextState<StateWait, Hero*, ScriptKind>(objPtr(), static_cast<ScriptKind>(0xC));
        }
    }
}

void StateSliding::procMove() {
    gobj::MoveParamDecel decel =
        mFrame < obj().param().common()._1A8   ? obj().param().common()._2C
        : mFrame < obj().param().common()._1AC ? obj().param().common()._1B0
                                               : obj().param().common()._1B4;
    obj().move().groundDecel(decel);
}

void StateSliding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        return;
    }
    f32 max = obj().param().common()._1C4;
    f32 x = obj().move().velocity().x;
    if (hel::math::Math::AbsF32(x) > max) {
        max *= x < 0.0f ? -1 : 1;
        obj().move().setSpeedH(max);
    }
    obj().hid().cancelTrigger(0x30);
    obj().stateChanger().setNextState<StateJumpHold, Hero*, bool>(objPtr(), false);
}

bool StateSliding::procObjCollReact() {
    if (obj().objColl().objColl().isAttackCollide() && Utility::CanBoundByCheapAttack(obj())) {
        obj().stateChanger().setNextState<StateSlidingHit, Hero*>(objPtr());
        return true;
    }
    return false;
}

}
}
}
}
