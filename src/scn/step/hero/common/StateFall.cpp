#include "scn/step/hero/common/StateFall.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hang.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Stepping.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/VacuumReceiver.h"
#include "scn/step/hero/common/StateAirJump.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StatePlancher.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateSquashRoof.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "scn/step/hero/gimmick/StateHangSwitchWait.h"
#include "scn/step/hero/gimmick/StateRopeFlatWait.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateFall::StateFall(Hero* hero)
    : StateBase(hero)
    , _8(false)
    , mFrame(0)
    , mFallLength(0.0f)
    , mIsPassThroughLand(false) {
    construct();
}

StateFall::StateFall(Hero* hero, bool flag)
    : StateBase(hero)
    , _8(flag)
    , mFrame(0)
    , mFallLength(0.0f)
    , mIsPassThroughLand(false) {
    construct();
}

StateFall::~StateFall() {
    obj().stateChecker().setRun(false);
}

void StateFall::procAnim() {
    mFrame++;
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) ||
        gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr()) || StateCarryItemCatch::TryToChangeState(objPtr()) ||
        StateCarryItemPut::TryToChangeState(objPtr()) || StateCarryItemThrow::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateVomit::TryToChangeState(objPtr()) ||
        StateVacuum::TryToChangeState(objPtr()) || StateLadder::TryToChangeState(objPtr()) ||
        StateHover::TryToChangeState(objPtr()) || StateAirJump::TryToChangeState(objPtr()) ||
        StateSquashRoof::TryToChangeState(objPtr())) {
        return;
    }
    if (mIsPassThroughLand && mFrame < 10) {
        obj().mapColl().setTriggerPassThroughLand();
    }
    if (obj().model().isAllEnd()) {
        obj().model().script().start(2);
    }
    if (StatePlancher::CanPlancher(objPtr())) {
        f32 y = obj().location().pos().y;
        f32 prevY = obj().location().prevPos().y;
        if (y < prevY) {
            mFallLength += prevY - y;
        } else {
            mFallLength = 0.0f;
        }
        if (mFallLength >= obj().param().common()._22C) {
            obj().stateChanger().setNextState<StatePlancher, Hero*>(objPtr());
            return;
        }
    }
    if (obj().move().velocity().y < 0.0f) {
        obj().piggyback().setEnableRide(true);
        obj().stepping().setEnableStep(true);
    }
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(2));
}

void StateFall::procMove() {
    Utility::MoveDefault(obj());
}

void StateFall::procFixPos() {
    if (obj().mapColl().isPassThroughLand()) {
        return;
    }
    Utility::MapCollReactDefaultAction(obj());
    if (StateRun::TryToChangeState(objPtr()) || StateWait::TryToChangeStateWithScript(objPtr(), SCRIPT_KIND_3)) {
        return;
    }
}

void StateFall::construct() {
    obj().footState().setAir();
    if (!_8) {
        Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(2));
    }
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    obj().hang().setCanHang(true);
    obj().vacuumReceiver().setIsValid(true);
    mIsPassThroughLand = obj().mapColl().isPassThroughLand();
    obj().additionalMove().setEnableAirFlowOffset(true);
}

}}}}  // namespace scn::step::hero::common
