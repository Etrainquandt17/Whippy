#include "scn/step/hero/common/StateWalk.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/carryitem/User.h"
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
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateSquashWall.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/hero/gimmick/StateEnterDoor.h"
#include "scn/step/hero/gimmick/StateEnterLvMapDoor.h"
#include "scn/step/hero/gimmick/StateEnterMahoroa.h"
#include "scn/step/hero/gimmick/StateEnterShipDoor.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateWalk::TryToChangeState(Hero* hero) {
    if (!hero->mapColl().result().mIsHitFloor) {
        return false;
    }
    if (Utility::IsPressHDirKeySameTarget(*hero)) {
        Vector2 dir(0.01f * hero->target().getSign(), 0.0f);
        if (hero->mapColl().precheck(dir * 2.0f)._2) {
            return false;
        }
    }
    if (Utility::IsPressHDirKey(*hero)) {
        hero->stateChecker().setVacuumReceiverNoReset(true);
        hero->stateChanger().setNextState<StateWalk, Hero*>(hero);
        return true;
    }
    return false;
}

StateWalk::StateWalk(Hero* hero)
    : StateBase(hero)
    , mIsVacuum(obj().vacuumAttacker().vacuumCount() != 0) {
    obj().footState().setGround();
    Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(4));
    obj().piggyback().setEnableReceive(true);
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    obj().vacuumReceiver().setIsValid(true);
    obj().carryItemUser().setIsWalk(true);
}

StateWalk::~StateWalk() {
    obj().carryItemUser().setIsWalk(false);
}

void StateWalk::procAnim() {
    obj().abilityManager().chkDiscardAbility();
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
        StateCarryItemCatch::TryToChangeState(objPtr())) {
        return;
    }
    if (!Utility::IsPressHDirKey(obj())) {
        StateWait::TryToChangeState(objPtr());
        return;
    }
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(4));
    if (mIsVacuum && obj().vacuumAttacker().vacuumCount() == 0) {
        mIsVacuum = false;
        obj().model().script().start(4);
    }
}

void StateWalk::procMove() {
    Utility::MoveDefault(obj());
}

void StateWalk::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChecker().setVacuumReceiverNoReset(true);
        obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
        return;
    }
    if (StateSquashWall::TryToChangeState(objPtr())) {
        return;
    }
}

}}}}  // namespace scn::step::hero::common
