#include "scn/step/hero/common/StateJumpHold.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hang.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateAirJump.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
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

StateJumpHold::StateJumpHold(Hero* hero, bool flag)
    : StateBase(hero)
    , _8(flag)
    , mFrame(0) {
    obj().footState().setAir();
    if (_8) {
        obj().model().script().start(7);
        obj().model().anim().setFrameRate(1.75f);
    } else {
        Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(2));
    }
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    obj().hang().setCanHang(true);
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().stateChecker().set_4c(2);
}

StateJumpHold::~StateJumpHold() {
    obj().stateChecker().setRun(false);
}

void StateJumpHold::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) ||
        gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateVomit::TryToChangeState(objPtr()) || StateVacuum::TryToChangeState(objPtr()) ||
        StateLadder::TryToChangeState(objPtr()) || StateHover::TryToChangeState(objPtr()) ||
        StateAirJump::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().move().velocity().y < 0.0f) {
        if (++mFrame >= obj().param().common()._164) {
            obj().stateChanger().setNextState<StateFall, Hero*, bool>(objPtr(), _8);
        }
    }
}

void StateJumpHold::procMove() {
    gobj::MoveParamFall fall =
        obj().move().velocity().y > 0.0f ? obj().param().common()._168 : obj().param().common()._174;
    const gobj::MoveParamAccel& accel =
        obj().stateChecker().isRun() ? obj().param().common()._84 : obj().param().common()._78;
    Utility::MoveFromKeyState(obj(), accel, obj().param().common()._74, fall);
}

void StateJumpHold::procFixPos() {}

}
}
}
}
