#include "scn/step/hero/common/StateWaterWait.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
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
#include "scn/step/hero/common/StateWaterWalk.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateWaterWait::TryToChangeState(Hero* hero) {
    if (!Utility::CanWaterLanding(*hero)) {
        return false;
    }
    if (hero->mapColl().result().mIsHitFloor) {
        hero->stateChanger().setNextState<StateWaterWait, Hero*>(hero);
        return true;
    }
    return false;
}

bool StateWaterWait::TryToChangeStateWithScript(Hero* hero, u32 script) {
    if (!Utility::CanWaterLanding(*hero)) {
        return false;
    }
    if (hero->mapColl().result().mIsHitFloor) {
        hero->stateChanger().setNextState<StateWaterWait, Hero*, u32>(hero, script);
        return true;
    }
    return false;
}

StateWaterWait::StateWaterWait(Hero* hero)
    : StateBase(hero) {
    construct(0x1C);
}

StateWaterWait::StateWaterWait(Hero* hero, u32 script)
    : StateBase(hero) {
    construct(script);
}

StateWaterWait::~StateWaterWait() {
    obj().runChecker().cancelContinue();
}

void StateWaterWait::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (!Utility::CanWaterLanding(obj())) {
        obj().stateChanger().setNextState<StateSwim, Hero*>(objPtr());
        return;
    }
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) || StateCarryItemPut::TryToChangeState(objPtr()) ||
        StateCarryItemThrow::TryToChangeState(objPtr()) || obj().abilityManager().tryToChangeState() ||
        StateDrink::TryToChangeState(objPtr()) || StateVomit::TryToChangeState(objPtr()) ||
        StateWaterPistol::TryToChangeState(objPtr()) || Utility::TryToPassThroughLandOnBombDanger(obj()) ||
        StateSwim::TryToChangeState(objPtr()) || StateWaterWalk::TryToChangeState(objPtr()) ||
        StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        obj().model().script().start(0x1C);
    }
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(0x1C));
}

void StateWaterWait::procMove() {
    obj().move().groundDecel(obj().param().common()._A8._0);
}

void StateWaterWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateSwim, Hero*>(objPtr());
    }
}

void StateWaterWait::construct(u32 script) {
    obj().footState().setGround();
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(script));
    obj().piggyback().unlinkAll();
}

}}}}  // namespace scn::step::hero::common
