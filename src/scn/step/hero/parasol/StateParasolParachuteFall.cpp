#include "scn/step/hero/parasol/StateParasolParachuteFall.h"
#include "gobj/FootState.h"
#include "gobj/GearAnim.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Stepping.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateAirJump.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StatePlancher.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "scn/step/hero/gimmick/StateHangSwitchWait.h"
#include "scn/step/hero/gimmick/StateRopeFlatWait.h"
#include "scn/step/hero/parasol/Barrier.h"
#include "scn/step/hero/parasol/StateParasolDive.h"
#include "scn/step/hero/parasol/StateParasolParachute.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

StateParasolParachuteFall::StateParasolParachuteFall(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mFallFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(2);
    obj().model().weapon().anim().start(0xE, false);
    Barrier::SetValid(obj(), false);
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
}

StateParasolParachuteFall::~StateParasolParachuteFall() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        Barrier::SetValid(obj(), true);
        obj().stateChecker().setRun(false);
    }
}

// TODO: the map lists an unused function of 0xCC bytes in this unit, probably a TryToChangeState(Hero*).
void StateParasolParachuteFall::procAnim() {
    mFrame++;
    if (mFrame == 8) {
        Utility::CloseGearParasol(obj());
    }
    if (obj().abilityManager().chkDiscardAbility()) {
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (StateParasolDive::TryToChangeState(objPtr()) || common::StateLogout::TryToChangeState(objPtr())
        || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true)
        || gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr())
        || gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr())
        || gimmick::StateEnterShipDoor::TryToChangeState(objPtr())
        || gimmick::StateHangSwitchWait::TryToChangeState(objPtr())
        || gimmick::StateRopeFlatWait::TryToChangeState(objPtr())
        || common::StateCarryItemThrow::TryToChangeState(objPtr()) || common::StateVomit::TryToChangeState(objPtr())
        || common::StateVacuum::TryToChangeState(objPtr()) || common::StateLadder::TryToChangeState(objPtr())
        || common::StateHover::TryToChangeState(objPtr()) || common::StateAirJump::TryToChangeState(objPtr())
        || common::StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().hid().isTrigger(8)) {
        obj().stateChanger().setNextState<StateParasolParachute, Hero*>(objPtr());
        return;
    }
    if (obj().model().isAllEnd()) {
        obj().model().script().start(2);
    }
    if (++mFallFrame >= obj().param().common()._228 && common::StatePlancher::CanPlancher(objPtr())) {
        obj().stateChanger().setNextState<common::StatePlancher, Hero*>(objPtr());
        return;
    }
    if (obj().move().velocity().y < 0.0f) {
        obj().piggyback().setEnableRide(true);
        obj().stepping().setEnableStep(true);
    }
}

void StateParasolParachuteFall::procMove() {
    Utility::MoveDefault(obj());
}

void StateParasolParachuteFall::procFixPos() {
    if (common::StateRun::TryToChangeState(objPtr())
        || common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
        return;
    }
}

}
}
}
}
