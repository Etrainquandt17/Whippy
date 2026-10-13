#include "scn/step/hero/common/StateCarryItemCatchFloat.h"
#include "gobj/Move.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/common/StateWaterFloat.h"
#include "scn/step/hero/ride/StateStepShoeWait.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateCarryItemCatchFloat::TryToChangeState(Hero* hero) {
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
            hero->stateChanger().setNextState<ride::StateStepShoeWait, Hero*>(hero);
            return true;
        }
        hero->stateChanger().setNextState<StateCarryItemCatchFloat, Hero*>(hero);
        return true;
    }
    return false;
}

StateCarryItemCatchFloat::StateCarryItemCatchFloat(Hero* hero)
    : StateBase(hero) {
    obj().stateChecker().setFloat(true);
    obj().model().script().start(0x24);
    obj().model().subAnimControl().setLiftUpTwoHand(true);
}

StateCarryItemCatchFloat::~StateCarryItemCatchFloat() {
    obj().stateChecker().setFloat(false);
}

void StateCarryItemCatchFloat::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWaterFloat, Hero*>(objPtr());
    }
}

void StateCarryItemCatchFloat::procMove() {
    obj().move().airDecelFall(obj().param().common()._B8, gobj::MoveParamFall::Zero());
}

void StateCarryItemCatchFloat::procFixPos() {}

}}}}  // namespace scn::step::hero::common
