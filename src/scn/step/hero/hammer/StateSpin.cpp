#include "scn/step/hero/hammer/StateSpin.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/HammerParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/hammer/StateThrow.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateSpin::TryToChangeStateSpin(Hero* hero) {
    if (hero->footState().isGround() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSpin, Hero*, bool>(hero, false);
        return true;
    }
    return false;
}

bool StateSpin::TryToChangeStateThrow(Hero* hero) {
    if (hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (hero->footState().isGround() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x100)) {
        hero->stateChanger().setNextState<StateSpin, Hero*, bool>(hero, true);
        return true;
    }
    return false;
}

StateSpin::StateSpin(Hero* hero, bool isThrow)
    : StateBase(hero)
    , mIsThrow(isThrow)
    , mCanCancel(false)
    , mTurnWait(0) {
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().invincible().setPerm();
    obj().move().setSpeedH(obj().target().getSign() * param()._0);
    obj().model().script().start(0x132);
}

StateSpin::~StateSpin() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_HAMMER) {
        obj().model().subAnimControl().setLiftUpRHand(true);
    }
}

void StateSpin::procAnim() {
    if (obj().hid().isTrigger(0x100)) {
        mIsThrow = true;
    }
    if (obj().model().scriptTrigger().get(0)) {
        mCanCancel = true;
        obj().model().setFixDir(false);
        if (mIsThrow) {
            obj().stateChanger().setNextState<StateThrow, Hero*>(objPtr());
            return;
        }
    }
    if (mCanCancel && !mIsThrow) {
        if (common::StateJumpStart::TryToChangeState(objPtr()) || common::StateSquat::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSpin::procMove() {
    if (mTurnWait != 0) {
        mTurnWait--;
        obj().move().decel(gobj::MoveParamDecel::Zero());
        return;
    }
    if (mCanCancel) {
        hero::Utility::MoveDefaultNoOnIce(obj());
        return;
    }
    hero::Utility::MoveFromKeyState(obj(), param()._4, param()._10, obj().param().common()._90);
}

void StateSpin::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

bool StateSpin::procObjCollReact() {
    if (obj().mapColl().result().isHitWall()) {
        turn();
    }
    return false;
}

void StateSpin::turn() {
    hel::math::Vector3 velocity = obj().move().velocity();
    velocity.x *= -1.0f;
    obj().move().setVelocity(velocity);
    obj().target().invert();
    mTurnWait = 5;
}

const HammerParamSpin& StateSpin::param() const {
    if (mIsThrow) {
        return obj().param().hammer()._14;
    }
    return obj().param().hammer()._0;
}

}
}
}
}
