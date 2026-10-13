#include "scn/step/hero/sword/StateSwordAirSpin.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/Effect.h"
#include "gobj/FootState.h"
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
namespace sword {

bool StateSwordAirSpin::tryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordAirSpin, Hero*>(hero);
        return true;
    }
    return false;
}

StateSwordAirSpin::StateSwordAirSpin(Hero* hero)
    : StateBase(hero)
    , mIsEnd(false) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0x78);
    obj().landing().setValidAir(true);
    Utility::AirAttackInitSpeedV(obj());
}

StateSwordAirSpin::~StateSwordAirSpin() {
    obj().landing().setValidAir(false);
    if (!mIsEnd) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
    }
}

void StateSwordAirSpin::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
        mIsEnd = true;
    }
}

void StateSwordAirSpin::procMove() {
    Utility::MoveDefault(obj());
}

void StateSwordAirSpin::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::sword
