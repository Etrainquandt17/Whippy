#include "scn/step/hero/common/StateCopyPre.h"
#include "scn/step/Component.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateCopy.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateCopyPre::StateCopyPre(Hero* hero)
    : StateBase(hero)
    , mRequestor(obj().comp())
    , mIsChanged(false) {
    construct();
}

StateCopyPre::StateCopyPre(Hero* hero, const ::ostop::ReqHandle& handle)
    : StateBase(hero)
    , mRequestor(obj().comp(), handle)
    , mIsChanged(false) {
    construct();
}

StateCopyPre::~StateCopyPre() {
    Utility::SetSecondMoveIsValid(obj(), true);
    obj().stateChecker().setIsForbidSpaceJump(false);
    obj().stateChecker().setChallengeDoorWait(false);
    obj().setCanReactGimmick(true);
    obj().setCanCatchItem(true);
    if (!mIsChanged) {
        obj().abilityManager().clearAbility();
    }
    obj().stateChecker().setDrinkAbility(false);
    obj().water().setForbidChangeState(false);
}

void StateCopyPre::procAnim() {
    if (!mRequestor.isActive()) {
        if (!mRequestor.request(obj().stateChecker().is_51() ? static_cast<ostop::Flag>(0x11DF)
                                                              : static_cast<ostop::Flag>(0x11FF))) {
            return;
        }
    }
    if (obj().abilityManager().haveAbility()) {
        mIsChanged = true;
        obj().stateChanger().setNextState<StateCopy, Hero*, ::ostop::ReqHandle>(objPtr(), mRequestor.takeHandle());
    } else {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCopyPre::construct() {
    obj().model().script().start(0x29);
    obj().invincible().setPermNoFlash();
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().stateChecker().setIsForbidSpaceJump(true);
    obj().stateChecker().setChallengeDoorWait(true);
    obj().setCanReactGimmick(false);
    obj().setCanCatchItem(false);
    obj().stateChecker().setDrinkAbility(true);
    obj().water().setForbidChangeState(true);
}

}}}}  // namespace scn::step::hero::common
