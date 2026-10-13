#include "scn/step/hero/common/StateWaterWalk.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateDrink.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateSwim.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWaterPistol.h"
#include "scn/step/hero/common/StateWaterWait.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateWaterWalk::TryToChangeState(Hero* hero) {
    if (!Utility::CanWaterLanding(*hero)) {
        return false;
    }
    if (Utility::IsPressHDirKey(*hero)) {
        hero->stateChanger().setNextState<StateWaterWalk, Hero*>(hero);
        return true;
    }
    return false;
}

StateWaterWalk::StateWaterWalk(Hero* hero)
    : StateBase(hero) {
    obj().footState().setGround();
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(0x20));
}

StateWaterWalk::~StateWaterWalk() {
    obj().runChecker().cancelContinue();
}

// TODO: setNextState<StateSwim, Hero*> is called on StateChanger<hero::IState, 256> in the original (here and in procFixPos).
void StateWaterWalk::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (!Utility::CanWaterLanding(obj())) {
        obj().stateChanger().setNextState<StateSwim, Hero*>(objPtr());
        return;
    }
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        StateCarryItemPut::TryToChangeState(objPtr()) || StateCarryItemThrow::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateDrink::TryToChangeState(objPtr()) ||
        StateVomit::TryToChangeState(objPtr()) || StateWaterPistol::TryToChangeState(objPtr()) ||
        Utility::TryToPassThroughLandOnBombDanger(obj()) || StateSwim::TryToChangeState(objPtr()) ||
        StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (!Utility::IsPressHDirKey(obj())) {
        if (StateWaterWait::TryToChangeState(objPtr())) {
            return;
        }
    }
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(0x1C));
}

void StateWaterWalk::procMove() {
    Utility::MoveFromKeyState(obj(), obj().param().common()._A8._4, obj().param().common()._A8._0,
                              obj().param().common()._A8._2C);
}

void StateWaterWalk::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateSwim, Hero*>(objPtr());
    }
}

}
}
}
}
