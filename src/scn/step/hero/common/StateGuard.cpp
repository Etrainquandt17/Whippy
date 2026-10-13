#include "scn/step/hero/common/StateGuard.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Guard.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/PowerCharge.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/interference/StateSpaceJump.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

namespace {

bool canChangeState(Hero* hero) {
    if (hero->stateChecker().isBombDanger()) {
        return false;
    }
    if (hero->abilityManager().isForbidGuard()) {
        return false;
    }
    if (hero->footState().isGround() && hero->vacuumAttacker().vacuumCount() == 0 &&
        !hero->carryItemUser().isItemExist() && hero->hid().isHold(0x40)) {
        return true;
    }
    return false;
}

}

bool StateGuard::TryToChangeState(Hero* hero) {
    if (canChangeState(hero)) {
        hero->stateChanger().setNextState<StateGuard, Hero*, bool>(hero, true);
        return true;
    }
    return false;
}

bool StateGuard::TryToChangeStateContinue(Hero* hero) {
    if (canChangeState(hero)) {
        hero->stateChanger().setNextState<StateGuard, Hero*, bool>(hero, false);
        return true;
    }
    return false;
}

StateGuard::StateGuard(Hero* hero, bool isStart)
    : StateBase(hero) {
    obj().footState().setGround();
    obj().model().script().start(isStart ? static_cast<ScriptKind>(0x30) : static_cast<ScriptKind>(0x31));
    obj().piggyback().setEnableReceive(true);
    obj().guard().setGuard(true);
    obj().commandManager().resetHoldFrame(static_cast<ButtonMask>(0x200));
    obj().powerCharge().setCanCharge(true);
}

StateGuard::~StateGuard() {
    obj().guard().setGuard(false);
}

void StateGuard::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (!obj().isMainPlayer() && obj().hid().isHold(0x200) &&
        obj().commandManager().getHoldFrame(static_cast<ButtonMask>(0x200)) >= obj().param().common()._3AC) {
        obj().stateChanger().setNextState<interference::StateSpaceJump, Hero*, interference::StateSpaceJump::NextState>(
            objPtr(), interference::StateSpaceJump::NEXT_STATE_0);
        return;
    }
    if (!obj().hid().isHold(0x40) || obj().stateChecker().isBombDanger()) {
        obj().stateChanger().setNextState<StateWait, Hero*, ScriptKind>(objPtr(), static_cast<ScriptKind>(0x32));
    }
}

void StateGuard::procMove() {
    Utility::MoveGuard(obj());
}

void StateGuard::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
    }
}

}}}}  // namespace scn::step::hero::common
