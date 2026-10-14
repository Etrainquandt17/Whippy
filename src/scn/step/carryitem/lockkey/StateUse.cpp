#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/carryitem/lockkey/StateUse.h"

#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/carryitem/lockkey/StateFall.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"

using util::ObjRefHandle;

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem)
    , mIsHeroUser(false)
    , mFlash(*carryItem) {
    if (obj().getUser().wasSet()) {
        ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().getUser()->owner().uid());
        if (hero.isAlive()) {
            mIsHeroUser = true;
        }
    }
}

StateUse::~StateUse() {}

void StateUse::procAnim() {
    mUseAlgorithm.procAnim();
    if (mIsHeroUser) {
        obj().incUseCount();
    }
    if (obj().useCount() >= obj().param().lockKey()._4) {
        obj().deadWithEffect();
    } else {
        mFlash.update();
    }
}

void StateUse::procMove() {
    mUseAlgorithm.procMove();
}

void StateUse::procConstraint() {
    if (mUseAlgorithm.procConstraint()) {
        obj().stateChanger().setNextState<StateFall, CarryItem*>(objPtr());
    }
}

}}}}  // namespace scn::step::carryitem::lockkey
