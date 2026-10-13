#include "scn/step/hero/common/StatePlancher.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Stepping.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateAirJump.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StatePlancherHit.h"
#include "scn/step/hero/common/StatePlancherLanding.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "scn/step/hero/gimmick/StateHangSwitchWait.h"
#include "scn/step/hero/gimmick/StateRopeFlatWait.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StatePlancher::CanPlancher(Hero* hero) {
    if (hero->move().velocity().y >= 0.0f) {
        return false;
    }
    if (hero->vacuumAttacker().vacuumCount() != 0) {
        return false;
    }
    if (hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (hero->stateChecker().isBombDanger()) {
        return false;
    }
    return !hero->piggyback().isExistChild();
}

StatePlancher::StatePlancher(Hero* hero)
    : StateBase(hero)
    , mFallLength(0.0f) {
    init(true);
}

StatePlancher::StatePlancher(Hero* hero, bool flag)
    : StateBase(hero)
    , mFallLength(0.0f) {
    init(flag);
}

void StatePlancher::init(bool flag) {
    obj().footState().setAir();
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().stateChecker().setPlancher(true);
    if (flag) {
        obj().model().script().start(0x36);
    } else {
        obj().model().script().start(0x37);
    }
    obj().stepping().setEnableStep(true);
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    Utility::CloseGearParasol(obj());
    obj().additionalMove().setEnableAirFlowOffset(true);
}

StatePlancher::~StatePlancher() {
    obj().stateChecker().setRun(false);
    obj().stateChecker().setPlancher(false);
}

void StatePlancher::procAnim() {
    f32 y = obj().location().pos().y;
    f32 prevY = obj().location().prevPos().y;
    if (y < prevY) {
        mFallLength += prevY - y;
    } else {
        mFallLength = 0.0f;
    }
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) ||
        gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || StateCarryItemCatch::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateVacuum::TryToChangeState(objPtr()) ||
        StateLadder::TryToChangeState(objPtr()) || StateHover::TryToChangeState(objPtr()) ||
        StateAirJump::TryToChangeState(objPtr())) {
        return;
    }
}

void StatePlancher::procMove() {
    Utility::MoveDefault(obj());
}

void StatePlancher::procFixPos() {
    if (mFallLength >= obj().param().common()._230 && StatePlancherLanding::TryToChangeState(objPtr())) {
        return;
    }
    Utility::MapCollReactDefaultAction(obj());
    if (StateRun::TryToChangeState(objPtr()) || StateWait::TryToChangeStateWithScript(objPtr(), SCRIPT_KIND_3)) {
        return;
    }
}

bool StatePlancher::procObjCollReact() {
    if (obj().objColl().objColl().isAttackCollide()) {
        obj().stateChanger().setNextState<StatePlancherHit, Hero*>(objPtr());
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::hero::common
