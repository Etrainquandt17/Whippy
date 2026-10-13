#include "scn/step/hero/common/StateDrink.h"
#include "gobj/FootState.h"
#include "hid/RumbleRequestor.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateCopyPre.h"
#include "scn/step/hero/common/StateMixPre.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateDrink::TryToChangeState(Hero* hero) {
    if ((hero->vacuumAttacker().vacuumCount() != 0 && hero->footState().isGround() && hero->hid().isHold(4)) ||
        hero->vacuumAttacker().isEnfDrink()) {
        hero->stateChanger().setNextState<StateDrink, Hero*>(hero);
        return true;
    }
    return false;
}

StateDrink::StateDrink(Hero* hero)
    : StateBase(hero)
    , _8(0)
    , mIsSwallowed(false)
    , mIsKeepAbility(false)
    , mIsMix(false) {
    checkMix();
    bool isCopy = true;
    bool isOnDrink = false;
    if (!mIsMix) {
        if (obj().vacuumAttacker().abilityCount(vacuum::ABILITY_TYPE_0) != 0) {
            obj().abilityManager().initAbility(obj().vacuumAttacker().ability(vacuum::ABILITY_TYPE_0, 0));
        } else if (obj().vacuumAttacker().abilityCount(vacuum::ABILITY_TYPE_1) != 0) {
            obj().abilityManager().initAbility(obj().vacuumAttacker().ability(vacuum::ABILITY_TYPE_1, 0));
        } else if (obj().vacuumAttacker().abilityCount(vacuum::ABILITY_TYPE_2) != 0) {
            obj().abilityManager().initAbility(obj().vacuumAttacker().ability(vacuum::ABILITY_TYPE_2, 0));
            isOnDrink = true;
        } else if (obj().vacuumAttacker().abilityCount(vacuum::ABILITY_TYPE_3) != 0) {
            obj().abilityManager().initAbility(obj().vacuumAttacker().ability(vacuum::ABILITY_TYPE_3, 0));
        } else {
            isCopy = false;
        }
    }
    if (isOnDrink) {
        obj().vacuumAttacker().onDrink();
    }
    if (isCopy) {
        obj().vacuumAttacker().clearAbility();
        obj().invincible().setPermNoFlash();
        obj().stateChecker().setDrinkAbility(true);
    }
    obj().vacuumAttacker().resetVacuumCount();
    obj().vacuumAttacker().resetVacuumHold();
    obj().model().script().start(0x16);
    if (obj().isMainPlayer()) {
        obj().comp().gimmickManager().onDrink(obj().location().pos());
    }
    obj().additionalMove().setForbidChangeState(true);
    obj().nururi().setCanNururi(false);
    obj().stateChecker().setIsForbidSpaceJump(true);
    obj().water().setForbidChangeState(true);
}

StateDrink::~StateDrink() {
    obj().stateChecker().setIsForbidSpaceJump(false);
    obj().model().modelRotCtrl().resetRotTarget();
    if (!mIsKeepAbility) {
        obj().abilityManager().clearAbility();
    }
    obj().stateChecker().setDrinkAbility(false);
    obj().water().setForbidChangeState(false);
}

void StateDrink::procAnim() {
    if (!mIsSwallowed && obj().model().anim().frame() >= 14.0f) {
        mIsSwallowed = true;
        if (mIsMix) {
            obj().stateChanger().setNextState<StateMixPre, Hero*>(objPtr());
            return;
        }
        if (obj().abilityManager().haveAbility()) {
            obj().hidRumble().start(6);
            mIsKeepAbility = true;
            obj().stateChanger().setNextState<StateCopyPre, Hero*>(objPtr());
            return;
        }
        obj().hidRumble().start(5);
    }
    if (obj().model().isAllEnd()) {
        mIsKeepAbility = true;
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateDrink::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateDrink::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

void StateDrink::checkMix() {
    if (obj().vacuumAttacker().abilityCount(vacuum::ABILITY_TYPE_0) == 0 &&
        obj().vacuumAttacker().abilityCount(vacuum::ABILITY_TYPE_3) >= 3) {
        mIsMix = true;
    }
}

}
}
}
}
