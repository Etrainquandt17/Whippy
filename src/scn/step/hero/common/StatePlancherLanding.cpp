#include "scn/step/hero/common/StatePlancherLanding.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateDrink.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StatePlancher.h"
#include "scn/step/hero/common/StatePlancherBound.h"
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StatePlancherLanding::TryToChangeState(Hero* hero) {
    if (hero->mapColl().result().mIsHitFloor && StatePlancher::CanPlancher(hero)) {
        hero->stateChanger().setNextState<StatePlancherLanding, Hero*>(hero);
        return true;
    }
    return false;
}

StatePlancherLanding::StatePlancherLanding(Hero* hero)
    : StateBase(hero)
    , mSpeedH(0.0f)
    , mIsAirContinue(obj().runChecker().isAirContinue()) {
    obj().footState().setGround();
    mSpeedH = obj().move().velocity().x;
    obj().move().setSpeedV(0.0f);
    obj().stateChecker().setPlancher(true);
    obj().model().script().start(0x38);
}

StatePlancherLanding::~StatePlancherLanding() {
    obj().stateChecker().setPlancher(false);
}

void StatePlancherLanding::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || StateCarryItemCatch::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateDrink::TryToChangeState(objPtr()) ||
        StateSliding::TryToChangeState(objPtr()) || StateVacuum::TryToChangeState(objPtr()) ||
        StateSquat::TryToChangeState(objPtr()) || StateLadder::TryToChangeState(objPtr()) ||
        StateJumpStart::TryToChangeState(objPtr())) {
        if (mIsAirContinue) {
            obj().runChecker().setAirContinue();
        }
        return;
    }
    if (obj().model().isAllEnd()) {
        if (mIsAirContinue) {
            obj().runChecker().setAirContinue();
        }
        obj().move().setSpeedH(mSpeedH);
        obj().stateChanger().setNextState<StatePlancherBound, Hero*>(objPtr());
    }
}

void StatePlancherLanding::procMove() {
    obj().move().airDecelFall(obj().param().common()._74, obj().param().common()._90);
}

void StatePlancherLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}
}
}
}
