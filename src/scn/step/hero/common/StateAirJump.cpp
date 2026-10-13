#include "scn/step/hero/common/StateAirJump.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hang.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateRun.h"
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

bool StateAirJump::TryToChangeState(Hero* hero) {
    if (hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (!IndiviUtil::IsDee(hero->kind())) {
        return false;
    }
    MapCollResult result = hero->mapColl().result();
    if (!result.mIsHitFloor && hero->vacuumAttacker().vacuumCount() == 0 && hero->hid().isTrigger(0x10)) {
        hero->stateChanger().setNextState<StateAirJump, Hero*>(hero);
        return true;
    }
    return false;
}

StateAirJump::StateAirJump(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    if (obj().hang().isExistParent() && obj().move().velocity().y < 0.0f) {
        obj().move().setSpeedV(obj().move().velocity().y + obj().param().common()._1A0);
    } else {
        obj().move().setSpeedV(obj().param().common()._1A0);
    }
    obj().runChecker().cancelContinue();
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    obj().piggyback().setEnableRide(true);
    obj().hang().setCanReceive(true);
    obj().hang().setCanHang(true);
    obj().model().script().start(8);
}

StateAirJump::~StateAirJump() {}

void StateAirJump::procAnim() {
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateLadder::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd() && obj().move().velocity().y < 0.0f) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAirJump::procMove() {
    Utility::MoveDefault(obj());
}

void StateAirJump::procFixPos() {
    if (gimmick::StateHangSwitchWait::TryToChangeState(objPtr()) ||
        gimmick::StateRopeFlatWait::TryToChangeState(objPtr()) || StateAirJump::TryToChangeState(objPtr()) ||
        StateRun::TryToChangeState(objPtr()) || StateWait::TryToChangeStateWithScript(objPtr(), SCRIPT_KIND_3)) {
        return;
    }
}

}
}
}
}
