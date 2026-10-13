#include "scn/step/hero/common/StateVomit.h"
#include "gobj/FootState.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateVomit::TryToChangeState(Hero* hero) {
    if (hero->vacuumAttacker().vacuumCount() != 0 && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateVomit, Hero*>(hero);
        return true;
    }
    return false;
}

StateVomit::StateVomit(Hero* hero)
    : StateBase(hero)
    , mIsVomited(false) {
    obj().model().script().start(0x17);
    Utility::AirAttackInitSpeedV(obj());
    Utility::UpdateMoveTarget(obj());
    if (obj().footState().isAir()) {
        if (obj().runChecker().isAirContinue()) {
            obj().stateChecker().setRun(true);
        }
    } else if (obj().runChecker().isGroundContinue()) {
        obj().stateChecker().setRun(true);
    }
    if (obj().isMainPlayer()) {
        hel::math::Vector3 pos = obj().location().pos();
        obj().comp().gimmickManager().onVomit(pos);
    }
    obj().water().setForbidChangeState(true);
}

StateVomit::~StateVomit() {
    obj().stateChecker().setRun(false);
    obj().water().setForbidChangeState(false);
}

void StateVomit::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (!mIsVomited && obj().vacuumAttacker().vacuumCount() == 0) {
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
        return;
    }
    if (obj().model().scriptTrigger().get(0)) {
        Utility::Vomit(obj(), false);
        mIsVomited = true;
    }
}

void StateVomit::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateVomit::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::common
