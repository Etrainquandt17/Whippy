#include "scn/step/hero/common/StateJump.h"
#include "gobj/FootState.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hang.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/Stepping.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateJumpHold.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateSquashRoof.h"
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

bool StateJump::TryToChangeState(Hero* hero) {
    return TryToChangeState(hero, true);
}

bool StateJump::TryToChangeState(Hero* hero, bool initSpeed) {
    if (hero->hid().isTrigger(0x10)) {
        hero->stateChanger().setNextState<StateJump, Hero*, bool>(hero, initSpeed);
        return true;
    }
    return false;
}

StateJump::StateJump(Hero* hero, bool initSpeed, bool flag)
    : StateBase(hero)
    , mFrame(0)
    , mHoldFrame(0)
    , _10(flag) {
    construct(initSpeed);
}

StateJump::StateJump(Hero* hero, u32 frame, bool initSpeed, bool flag)
    : StateBase(hero)
    , mFrame(0)
    , mHoldFrame(frame)
    , _10(flag) {
    construct(initSpeed);
}

StateJump::~StateJump() {
    obj().stateChecker().setRun(false);
}

void StateJump::procAnim() {
    mFrame++;
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) ||
        gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateVomit::TryToChangeState(objPtr()) || StateVacuum::TryToChangeState(objPtr()) ||
        StateLadder::TryToChangeState(objPtr()) || StateSquashRoof::TryToChangeState(objPtr())) {
        return;
    }
    if (mHoldFrame == 0 && !obj().hid().isHold(0x10) && (!_10 || !obj().hid().isHold(8))) {
        obj().stateChanger().setNextState<StateJumpHold, Hero*, bool>(objPtr(), doEnableRotAnim());
        return;
    }
    if (mHoldFrame != 0) {
        mHoldFrame--;
    }
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(6));
}

void StateJump::procMove() {
    Utility::MoveDefault(obj());
    if (obj().move().velocity().y <= 0.0f) {
        obj().stateChanger().setNextState<StateJumpHold, Hero*, bool>(objPtr(), doEnableRotAnim());
    }
}

void StateJump::procFixPos() {
}

void StateJump::construct(bool initSpeed) {
    obj().footState().setAir();
    if (initSpeed) {
        obj().move().setSpeedV(obj().param().common()._158);
    }
    if (obj().runChecker().isAirContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().stateChecker().set_14(14);
    obj().stepping().setEnableReceive(true);
    obj().hang().setCanHang(true);
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    obj().stateChecker().set_4c(2);
    Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(6));
}

bool StateJump::doEnableRotAnim() const {
    return isSafe() && mFrame > obj().param().common()._160;
}

}}}}  // namespace scn::step::hero::common
