#include "scn/step/hero/common/StateLogout.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/carryitem/User.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Dead.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/InitiativeUtil.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/LogoutController.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/info/InfoControl.h"
#include "scn/step/info/Manager.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateLogout::TryToChangeState(Hero* hero) {
    if (InitiativeUtil::IsMine(*hero)) {
        return false;
    }
    if (hero->logoutController().canLogout()) {
        hero->stateChanger().setNextState<StateLogout, Hero*>(hero);
        return true;
    }
    return false;
}

StateLogout::StateLogout(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().hitStop().clear();
    obj().move().resetVelocity();
    obj().mapColl().setValid(false);
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().invincible().clearMighty();
    obj().invincible().clear();
    obj().objColl().setXlu();
    obj().dead().setForbid(true);
    obj().model().subAnimControl().clearAll();
    obj().piggyback().unlinkAll();
    obj().carryItemUser().clearTargetItem();
    obj().comp().cameraController().resetIntpRate();
    obj().vacuumAttacker().resetVacuumCount();
    obj().vacuumAttacker().resetVacuumReserve();
    obj().vacuumAttacker().resetVacuumHold();
    obj().abilityManager().changeAbilityIfPossible();
    obj().abilityManager().dropAbility();
    obj().logoutController().returnRestPlayer();
    if (obj().comp().infoManager().isInfoControl()) {
        obj().comp().infoManager().infoControl().setIsPlayerOut(true);
    }
    if (!obj().dead().isDead()) {
        obj().comp().permEffect().powerful().requestP(static_cast<effect::Kind>(0xB0), obj().location().pos());
        obj().comp().permSoundSE().start(0xED);
    }
    obj().comp().heroManager().removeHero(obj().padChan());
}

StateLogout::~StateLogout() {}

void StateLogout::procAnim() {}

void StateLogout::procMove() {}

void StateLogout::procFixPos() {}

}
}
}
}
