#include "scn/step/hero/common/StateWait.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/VacuumReceiver.h"
#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/hero/common/StateDrink.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateGuard.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateLogout.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWalk.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterMahoroa.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateWait::TryToChangeState(Hero* hero) {
    if (hero->mapColl().result().mIsHitFloor) {
        hero->stateChecker().setVacuumReceiverNoReset(true);
        hero->stateChanger().setNextState<StateWait, Hero*>(hero);
        return true;
    }
    return false;
}

bool StateWait::TryToChangeStateWithScript(Hero* hero, ScriptKind script) {
    if (hero->mapColl().result().mIsHitFloor) {
        hero->stateChecker().setVacuumReceiverNoReset(true);
        hero->stateChanger().setNextState<StateWait, Hero*, ScriptKind>(hero, script);
        return true;
    }
    return false;
}

StateWait::StateWait(Hero* hero)
    : StateBase(hero)
    , mScript(static_cast<ScriptKind>(0)) {
    if (obj().stateChecker().isSparkCharging()) {
        mScript = static_cast<ScriptKind>(0xD3);
    }
    construct();
}

StateWait::StateWait(Hero* hero, ScriptKind script)
    : StateBase(hero)
    , mScript(script) {
    construct();
}

StateWait::~StateWait() {
    obj().stateChecker().setWait(false);
}

void StateWait::procAnim() {
    bool isDiscard = false;
    if (obj().abilityManager().chkDiscardAbility()) {
        isDiscard = true;
        if (obj().model().script().currentScriptIndex() == 0xD3) {
            obj().model().script().start(0);
        }
    }
    if (StateLogout::TryToChangeState(objPtr()) || gimmick::StateEnterDoor::TryToChangeState(objPtr(), true) ||
        gimmick::StateEnterLvMapDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterChallengeDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterShipDoor::TryToChangeState(objPtr()) ||
        gimmick::StateEnterMahoroa::TryToChangeState(objPtr(), true) ||
        StateCarryItemPut::TryToChangeState(objPtr()) || StateCarryItemThrow::TryToChangeState(objPtr()) ||
        obj().abilityManager().tryToChangeState() || StateDrink::TryToChangeState(objPtr()) ||
        StateSliding::TryToChangeState(objPtr()) || StateVomit::TryToChangeState(objPtr()) ||
        StateVacuum::TryToChangeState(objPtr()) || Utility::TryToPassThroughLandOnBombDanger(obj()) ||
        StateSquat::TryToChangeState(objPtr()) || StateLadder::TryToChangeState(objPtr()) ||
        StateJumpStart::TryToChangeState(objPtr()) || StateGuard::TryToChangeState(objPtr()) ||
        StateRun::TryToChangeState(objPtr()) || StateWalk::TryToChangeState(objPtr()) ||
        StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().isAllEnd()) {
        if (!isDiscard && obj().stateChecker().isSparkCharging()) {
            obj().model().script().start(0xD3);
        } else {
            obj().model().script().start(0);
        }
        return;
    }
    if (!isDiscard) {
        bool isSpark = obj().model().script().currentScriptIndex() == 0xD3;
        if (isSpark && !obj().stateChecker().isSparkCharging()) {
            obj().model().script().start(0);
        } else if (!isSpark && obj().stateChecker().isSparkCharging()) {
            obj().model().script().start(0xD3);
        }
    }
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(0));
}

void StateWait::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateWait::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChecker().setVacuumReceiverNoReset(true);
        obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
    }
}

void StateWait::construct() {
    obj().footState().setGround();
    Utility::SwitchBombDangerMotionInit(obj(), mScript);
    obj().piggyback().setEnableReceive(true);
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    obj().vacuumReceiver().setIsValid(true);
    obj().stateChecker().setWait(true);
}

}}}}  // namespace scn::step::hero::common
