#include "scn/step/hero/common/StateJumpStart.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/InertialMove.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateJump.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "scn/step/hero/gimmick/StateHangSwitchWait.h"
#include "scn/step/hero/gimmick/StateRopeFlatWait.h"
#include "scn/step/map/LandManager.h"
#include "scn/step/map/MoveGroupAccessor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateJumpStart::TryToChangeState(Hero* hero) {
    if (hero->mapColl().result().mIsHitFloor && hero->hid().isTrigger(0x10)) {
        if (hero->stateChecker().isBombDanger()) {
            hero->stateChanger().setNextState<StateJump, Hero*>(hero);
        } else {
            hero->stateChanger().setNextState<StateJumpStart, Hero*>(hero);
        }
        return true;
    }
    return false;
}

StateJumpStart::StateJumpStart(Hero* hero)
    : StateBase(hero)
    , mSpeedH(obj().move().velocity().x)
    , mSpeedV(0.0f) {
    obj().footState().setAir();
    mSpeedV = obj().param().common()._158;
    if (obj().mapColl().result().groupFloor().isValid()) {
        obj().inertialMove().setVelocity(hel::math::Vector3(
            obj().comp().mapLandManager().mgAccessor().deltaSafe(obj().mapColl().result().groupFloor().no())
                .x,
            0.0f, 0.0f));
    }
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().stateChecker().setJumpStart(true);
    obj().stateChecker().set_4c(2);
    obj().stateChecker().set_64(2);
    obj().model().script().start(5);
}

StateJumpStart::~StateJumpStart() {
    obj().stateChecker().setJumpStart(false);
    obj().stateChecker().setRun(false);
}

void StateJumpStart::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) ||
        gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateVomit::TryToChangeState(objPtr()) || StateVacuum::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        obj().move().setSpeedH(mSpeedH);
        obj().move().setSpeedV(mSpeedV);
        obj().stateChanger().setNextState<StateJump, Hero*, bool>(objPtr(), false);
    }
}

void StateJumpStart::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateJumpStart::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::common
