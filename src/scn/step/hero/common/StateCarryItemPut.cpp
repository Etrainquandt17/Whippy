#include "scn/step/hero/common/StateCarryItemPut.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/common/StateAirJump.h"
#include "scn/step/hero/common/StateDrink.h"
#include "scn/step/hero/common/StateGuard.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateJumpStart.h"
#include "scn/step/hero/common/StateLadder.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateSliding.h"
#include "scn/step/hero/common/StateSquat.h"
#include "scn/step/hero/common/StateSwim.h"
#include "scn/step/hero/common/StateVacuum.h"
#include "scn/step/hero/common/StateVomit.h"
#include "scn/step/hero/common/StateWalk.h"
#include "scn/step/hero/common/StateWaterWalk.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateCarryItemPut::TryToChangeState(Hero* hero) {
    if (!hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (hero->hid().isTrigger(0x20) && hero->hid().isHold(4)) {
        hero->stateChanger().setNextState<StateCarryItemPut, Hero*>(hero);
        return true;
    }
    return false;
}

StateCarryItemPut::StateCarryItemPut(Hero* hero)
    : StateBase(hero)
    , mIsTrigger1(false) {
    obj().model().script().start(0x26);
    Utility::AirAttackInitSpeedV(obj());
    obj().model().subAnimControl().setLiftUpTwoHand(false);
    obj().wearBack().setBack();
}

StateCarryItemPut::~StateCarryItemPut() {
    if (obj().carryItemUser().isItemExist()) {
        obj().model().subAnimControl().setLiftUpTwoHand(true);
    }
}

void StateCarryItemPut::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().carryItemUser().isItemExist() && obj().model().scriptTrigger().get(0)) {
        obj().carryItemUser().set_4C(1);
        obj().carryItemUser().set_48(0);
        obj().carryItemUser().clearTargetItem();
    }
    if (!mIsTrigger1 && obj().model().scriptTrigger().get(1)) {
        mIsTrigger1 = true;
    }
    if (!mIsTrigger1) {
        obj().hid().setIgnoreInputUntilRelease(0x20);
    }
    if (mIsTrigger1) {
        if (obj().water().isInWater()) {
            if (obj().abilityManager().tryToChangeState() || StateSwim::TryToChangeState(objPtr()) ||
                StateWaterWalk::TryToChangeState(objPtr())) {
                return;
            }
        } else if (obj().abilityManager().tryToChangeState() || StateDrink::TryToChangeState(objPtr()) ||
                   StateSliding::TryToChangeState(objPtr()) || StateVomit::TryToChangeState(objPtr()) ||
                   StateVacuum::TryToChangeState(objPtr()) || StateHover::TryToChangeState(objPtr()) ||
                   StateAirJump::TryToChangeState(objPtr()) || StateSquat::TryToChangeState(objPtr()) ||
                   StateLadder::TryToChangeState(objPtr()) || StateJumpStart::TryToChangeState(objPtr()) ||
                   StateGuard::TryToChangeState(objPtr()) || StateRun::TryToChangeState(objPtr()) ||
                   StateWalk::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCarryItemPut::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateCarryItemPut::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::common
