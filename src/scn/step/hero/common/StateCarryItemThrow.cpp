#include "scn/step/hero/common/StateCarryItemThrow.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
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

bool StateCarryItemThrow::TryToChangeState(Hero* hero) {
    if (!hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCarryItemThrow, Hero*>(hero);
        return true;
    }
    return false;
}

StateCarryItemThrow::StateCarryItemThrow(Hero* hero)
    : StateBase(hero)
    , mHoldFrame(1)
    , mIsHold(true) {
    obj().model().script().start(0x25);
    Utility::AirAttackInitSpeedV(obj());
    obj().model().subAnimControl().setLiftUpTwoHand(false);
    obj().wearBack().setBack();
}

StateCarryItemThrow::~StateCarryItemThrow() {
    if (obj().carryItemUser().isItemExist()) {
        obj().model().subAnimControl().setLiftUpTwoHand(true);
    }
}

void StateCarryItemThrow::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (mIsHold) {
        if (obj().hid().isHold(0x20)) {
            obj().model().anim().setFrameRate(obj().param().common()._23C);
            mHoldFrame++;
        } else {
            mIsHold = false;
            obj().model().anim().setFrameRate(1.0f);
        }
        if (obj().model().anim().frame() >= obj().param().common()._240) {
            mIsHold = false;
            obj().model().anim().setFrameRate(1.0f);
        }
    }
    if (obj().carryItemUser().isItemExist() && obj().model().anim().frame() >= obj().param().common()._244) {
        obj().carryItemUser().set_48(mHoldFrame);
        obj().carryItemUser().set_4C(0);
        obj().carryItemUser().clearTargetItem();
    }
    if (obj().model().anim().frame() >= obj().param().common()._248) {
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
    } else if (!mIsHold) {
        obj().hid().setIgnoreInputUntilRelease(0x20);
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCarryItemThrow::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateCarryItemThrow::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
