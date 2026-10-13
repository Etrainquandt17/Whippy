#include "scn/step/hero/hammer/StateAirSpin.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Landing.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateAirSpin::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateAirSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateAirSpin::StateAirSpin(Hero* hero)
    : StateBase(hero)
    , mIsEnd(false) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().landing().setValidAir(true);
    obj().model().script().start(0x130);
    hero::Utility::AirAttackInitSpeedV(obj());
}

StateAirSpin::~StateAirSpin() {
    obj().landing().setValidAir(false);
    if (!mIsEnd) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
    }
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_HAMMER) {
        obj().model().subAnimControl().setLiftUpRHand(true);
    }
}

void StateAirSpin::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
        mIsEnd = true;
    }
}

void StateAirSpin::procMove() {
    hero::Utility::MoveDefault(obj());
}

void StateAirSpin::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}
}
}
}
