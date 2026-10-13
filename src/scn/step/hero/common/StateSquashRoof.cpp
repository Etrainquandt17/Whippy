#include "scn/step/hero/common/StateSquashRoof.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateSquashRoof::TryToChangeState(Hero* hero) {
    MapCollResult result = hero->mapColl().result();
    if (hero->move().velocity().y > 0.0f && result.mIsHitRoof) {
        hero->stateChanger().setNextState<StateSquashRoof, Hero*>(hero);
        return true;
    }
    return false;
}

StateSquashRoof::StateSquashRoof(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0x3B);
    obj().move().resetSpeedV();
}

StateSquashRoof::~StateSquashRoof() {}

void StateSquashRoof::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateCarryItemThrow::TryToChangeState(objPtr()) ||
        StateCarryItemPut::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateVomit::TryToChangeState(objPtr()) || StateVacuum::TryToChangeState(objPtr()) ||
        StateLadder::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSquashRoof::procMove() {
    if (Utility::IsPressHDirKey(obj())) {
        Utility::UpdateMoveTarget(obj());
        const gobj::MoveParamAccel& accel =
            obj().stateChecker().isRun() ? obj().param().common()._84 : obj().param().common()._78;
        obj().move().airAccelFall(obj().target().isRightDir(), accel, obj().param().common()._90);
    } else {
        obj().move().airDecelFall(obj().param().common()._74, gobj::MoveParamFall::Zero());
    }
}

void StateSquashRoof::procFixPos() {}

}
}
}
}
