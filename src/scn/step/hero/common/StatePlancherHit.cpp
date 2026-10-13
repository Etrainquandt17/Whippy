#include "scn/step/hero/common/StatePlancherHit.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateAirJump.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StatePlancher.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StatePlancherHit::StatePlancherHit(Hero* hero)
    : StateBase(hero)
    , mFallLength(0.0f) {
    obj().footState().setAir();
    obj().move().setSpeedV(obj().param().common()._238);
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().model().script().start(0x3A);
    Utility::CloseGearParasol(obj());
}

StatePlancherHit::~StatePlancherHit() {
    obj().stateChecker().setRun(false);
}

void StatePlancherHit::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateVacuum::TryToChangeState(objPtr()) || StateLadder::TryToChangeState(objPtr()) ||
        StateHover::TryToChangeState(objPtr()) || StateAirJump::TryToChangeState(objPtr())) {
        return;
    }
    f32 y = obj().location().pos().y;
    f32 prevY = obj().location().prevPos().y;
    if (y < prevY) {
        mFallLength += prevY - y;
    } else {
        mFallLength = 0.0f;
    }
    if (mFallLength >= obj().param().common()._234) {
        obj().stateChanger().setNextState<StatePlancher, Hero*>(objPtr());
    }
}

void StatePlancherHit::procMove() {
    gobj::MoveParamFall fall =
        obj().move().velocity().y > 0.0f ? obj().param().common()._9C : obj().param().common()._90;
    const gobj::MoveParamAccel& accel =
        obj().stateChecker().isRun() ? obj().param().common()._84 : obj().param().common()._78;
    Utility::MoveFromKeyState(obj(), accel, obj().param().common()._74, fall);
}

void StatePlancherHit::procFixPos() {
    if (StateRun::TryToChangeState(objPtr()) || StateWait::TryToChangeStateWithScript(objPtr(), SCRIPT_KIND_3)) {
        return;
    }
}

}
}
}
}
