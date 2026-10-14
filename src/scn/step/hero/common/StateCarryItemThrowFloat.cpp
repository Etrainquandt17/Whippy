#include "scn/step/hero/common/StateCarryItemThrowFloat.h"
#include "gobj/Move.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/common/StateWaterFloat.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateCarryItemThrowFloat::TryToChangeState(Hero* hero) {
    if (!hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCarryItemThrowFloat, Hero*>(hero);
        return true;
    }
    return false;
}

StateCarryItemThrowFloat::StateCarryItemThrowFloat(Hero* hero)
    : StateBase(hero)
    , mHoldFrame(1)
    , mIsHold(true) {
    obj().stateChecker().setFloat(true);
    obj().model().script().start(0x25);
    obj().model().subAnimControl().setLiftUpTwoHand(false);
    obj().wearBack().setBack();
}

StateCarryItemThrowFloat::~StateCarryItemThrowFloat() {
    obj().stateChecker().setFloat(false);
    if (obj().carryItemUser().isItemExist()) {
        obj().model().subAnimControl().setLiftUpTwoHand(true);
    }
}

void StateCarryItemThrowFloat::procAnim() {
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
        obj().carryItemUser().clearTargetItem();
    }
    if (obj().model().anim().frame() >= obj().param().common()._248) {
        if (obj().abilityManager().tryToChangeState()) {
            return;
        }
    } else if (!mIsHold) {
        obj().hid().setIgnoreInputUntilRelease(0x20);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWaterFloat, Hero*>(objPtr());
    }
}

void StateCarryItemThrowFloat::procMove() {
    obj().move().airDecelFall(obj().param().common()._B8, gobj::MoveParamFall::Zero());
}

void StateCarryItemThrowFloat::procFixPos() {}

}}}}  // namespace scn::step::hero::common
