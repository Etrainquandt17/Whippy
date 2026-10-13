#include "scn/step/hero/common/StateRun.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Kiss.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
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
#include "scn/step/hero/hammer/StateSpin.h"
#include "scn/step/hero/ice/StateSkate.h"
#include "scn/step/hero/water/StateWaterWaterRide.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateRun::TryToChangeState(Hero* hero) {
    if (!hero->mapColl().result().mIsHitFloor) {
        return false;
    }
    if (Utility::IsPressHDirKeySameTarget(*hero)) {
        if (hero->mapColl().precheck(hel::math::Vector2(0.01f * hero->target().getSign(), 0.0f))._2) {
            return false;
        }
    }
    if (hero->runChecker().isEnableRun()) {
        hero->stateChanger().setNextState<StateRun, Hero*>(hero);
        return true;
    }
    return false;
}

StateRun::StateRun(Hero* hero)
    : StateBase(hero)
    , mIsVacuum(obj().vacuumAttacker().vacuumCount() != 0) {
    obj().footState().setGround();
    Utility::UpdateMoveTarget(obj());
    Utility::SwitchBombDangerMotionInit(obj(), static_cast<ScriptKind>(0x18));
    obj().mapColl().setThroughOneSpace(true);
    obj().stateChecker().setRun(true);
    obj().objColl().objColl().bodyColl().changeAttackType(static_cast<ocoll::AttackType>(1));
    obj().piggyback().setEnableReceive(true);
    obj().kiss().setCanReceive(true);
    obj().kiss().setCanKiss(true);
    if (obj().isMainPlayer()) {
        obj().comp().gimmickManager().onRun(obj().location().pos());
    }
    obj().carryItemUser().setIsRun(true);
}

StateRun::~StateRun() {
    obj().mapColl().setThroughOneSpace(false);
    obj().stateChecker().setRun(false);
    obj().runChecker().setAirContinue();
    obj().runChecker().setGroundContinue();
    obj().carryItemUser().setIsRun(false);
}

void StateRun::procAnim() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_HAMMER &&
        hammer::StateSpin::TryToChangeStateThrow(objPtr())) {
        return;
    }
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
    Utility::SwitchBombDangerMotionProc(obj(), static_cast<ScriptKind>(0x18));
    if (!obj().stateChecker().isBombDanger() && !obj().abilityManager().isReservedChange()) {
        if (obj().abilityManager().abilityKind() == ABILITY_KIND_WATER) {
            obj().stateChanger().setNextState<water::StateWaterWaterRide, Hero*>(objPtr());
            return;
        }
        if (obj().abilityManager().abilityKind() == ABILITY_KIND_ICE) {
            obj().stateChanger().setNextState<ice::StateSkate, Hero*>(objPtr());
            return;
        }
    }
    if (mIsVacuum && obj().vacuumAttacker().vacuumCount() == 0) {
        mIsVacuum = false;
        obj().model().script().start(0x18);
    }
}

void StateRun::procMove() {
    Utility::MoveDefault(obj());
}

void StateRun::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        obj().stateChanger().setNextState<StateFall, Hero*>(objPtr());
        return;
    }
    if (StateSquashWall::TryToChangeState(objPtr())) {
        return;
    }
}

}
}
}
}
