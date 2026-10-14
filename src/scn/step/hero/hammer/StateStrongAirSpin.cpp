#include "scn/step/hero/hammer/StateStrongAirSpin.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Landing.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateStrongAirSpin::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateStrongAirSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateStrongAirSpin::StateStrongAirSpin(Hero* hero)
    : StateBase(hero)
    , mIsEnd(false) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x131);
    obj().landing().setValidAir(true);
    hero::Utility::AirAttackInitSpeedV(obj());
}

StateStrongAirSpin::~StateStrongAirSpin() {
    obj().landing().setValidAir(false);
    if (!mIsEnd) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
    }
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_HAMMER) {
        obj().model().subAnimControl().setLiftUpRHand(true);
    }
}

void StateStrongAirSpin::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
        mIsEnd = true;
    }
}

void StateStrongAirSpin::procMove() {
    hero::Utility::MoveDefault(obj());
}

void StateStrongAirSpin::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::hammer
