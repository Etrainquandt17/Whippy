#include "scn/step/hero/hammer/StateHammerCharge.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/hammer/StateHammerAttack.h"
#include "scn/step/hero/hammer/StateTripleAttack.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateHammerCharge::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateHammerCharge, Hero*>(hero);
        return true;
    }
    return false;
}

StateHammerCharge::StateHammerCharge(Hero* hero)
    : StateBase(hero)
    , mIsCharged(false)
    , mIsEnd(false) {
    obj().footState().setGround();
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().setSELoopNoReset();
    obj().model().script().start(0x12B);
    hero::Utility::AirAttackInitSpeedV(obj());
}

StateHammerCharge::~StateHammerCharge() {
    if (!mIsEnd) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
    }
    obj().model().subAnimControl().setLiftUpRHand(true);
}

void StateHammerCharge::procAnim() {
    if (!mIsCharged && obj().model().scriptTrigger().get(0)) {
        mIsCharged = true;
    }
    if (common::StateJumpStart::TryToChangeState(objPtr())) {
        return;
    }
    if (!obj().hid().isHold(0x20)) {
        if (mIsCharged) {
            obj().stateChanger().setNextState<StateTripleAttack, Hero*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateHammerAttack, Hero*>(objPtr());
        }
        mIsEnd = true;
    }
}

void StateHammerCharge::procMove() {
    hero::Utility::MoveDefaultAction(obj());
}

void StateHammerCharge::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
