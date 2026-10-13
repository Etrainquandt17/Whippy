#include "scn/step/hero/common/StateCarryItemCatch.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateRun.h"
#include "scn/step/hero/common/StateSwim.h"
#include "scn/step/hero/common/StateWalk.h"
#include "scn/step/hero/common/StateWaterWait.h"
#include "scn/step/hero/ride/StateStepShoeWait.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateCarryItemCatch::TryToChangeState(Hero* hero) {
    if (hero->stateChecker().isForbidCarryCatch()) {
        return false;
    }
    if (hero->vacuumAttacker().vacuumCount() != 0) {
        return false;
    }
    if (hero->piggyback().isExistChild()) {
        return false;
    }
    if (hero->carryItemUser().isItemExist()) {
        return false;
    }
    if (hero->carryItemUser().chkCollide(hero->location().pos().getXY())) {
        if (hero->carryItemUser().targetItemKind() == 7) {
            hero->commandManager().setWait(BUTTON_MASK_10);
            hero->stateChanger().setNextState<ride::StateStepShoeWait, Hero*>(hero);
            return true;
        }
        hero->stateChanger().setNextState<StateCarryItemCatch, Hero*>(hero);
        return true;
    }
    return false;
}

StateCarryItemCatch::StateCarryItemCatch(Hero* hero)
    : StateBase(hero)
    , mIsTrigger0(false)
    , mIsTrigger1(false) {
    if (obj().runChecker().isGroundContinue()) {
        obj().stateChecker().setRun(true);
    }
    obj().model().script().start(0x24);
    Utility::AirAttackInitSpeedV(obj());
    obj().model().subAnimControl().setLiftUpTwoHand(true);
}

StateCarryItemCatch::~StateCarryItemCatch() {
    obj().stateChecker().setRun(false);
}

void StateCarryItemCatch::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().scriptTrigger().get(0)) {
        mIsTrigger0 = true;
    }
    if (obj().model().scriptTrigger().get(1)) {
        mIsTrigger1 = true;
    }
    if (mIsTrigger0) {
        if (obj().water().isInWater()) {
            if (Utility::CanWaterLanding(obj())) {
                MapCollResult result = obj().mapColl().result();
                if (result.mIsHitFloor) {
                    obj().stateChanger().setNextState<StateWaterWait, Hero*>(objPtr());
                    return;
                }
            }
        } else if (StateRun::TryToChangeState(objPtr()) || StateWalk::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (mIsTrigger1) {
        obj().stateChanger().setNextState<StateSwim, Hero*>(objPtr());
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateCarryItemCatch::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateCarryItemCatch::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::common
