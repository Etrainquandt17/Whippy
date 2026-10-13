#include "scn/step/hero/mike/StateCharge.h"
#include "gobj/Script.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MikeParam.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ShakeCharge.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/mike/StateAttack.h"
#include "scn/step/hero/mike/utility/Hat.h"
#include "scn/step/hero/mike/utility/Mike.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace mike {

bool StateCharge::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCharge, Hero*>(hero);
        return true;
    }
    return false;
}

StateCharge::StateCharge(Hero* hero)
    : StateBase(hero)
    , mIsCharged(false) {
    Utility::AirAttackInitSpeedV(obj());
    utility::Hat::Set(obj());
    utility::Mike::Set(obj());
    ShakeChargeEnv env = obj().param().mike()._0;
    obj().shakeCharge().setEnv(env._0, env._4, env._8, env._C);
    obj().shakeCharge().reset();
    obj().model().setSELoopNoReset();
    obj().model().script().start(0x188);
    obj().piggyback().unlinkAll();
}

StateCharge::~StateCharge() {
    utility::Hat::Wait(obj());
    utility::Mike::Clear(obj());
    obj().shakeCharge().reset();
}

void StateCharge::procAnim() {
    chkCharge();
    if (StateAttack::TryToChangeState(objPtr(), mIsCharged)) {
        return;
    }
}

void StateCharge::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateCharge::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

void StateCharge::chkCharge() {
    if (!isStandMike()) {
        return;
    }
    if (mIsCharged) {
        return;
    }
    u32 frame = obj().commandManager().getTriggerPastFrame(static_cast<ButtonMask>(0x20));
    mIsCharged = isShakeMax() && frame > 60;
    if (mIsCharged) {
        changeMotion();
    }
}

void StateCharge::changeMotion() {
    obj().model().script().start(0x18D);
    obj().effect()._58.requestN(static_cast<effect::Kind>(0x479), 0);
}

bool StateCharge::isStandMike() {
    return obj().abilityManager().abilityKind() == 0x1F;
}

bool StateCharge::isShakeMax() {
    return obj().shakeCharge().power() >= obj().param().mike()._0._8;
}

}
}
}
}
