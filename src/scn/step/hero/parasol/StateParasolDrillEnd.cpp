#include "scn/step/hero/parasol/StateParasolDrillEnd.h"
#include "gobj/Script.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/parasol/Barrier.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

StateParasolDrillEnd::StateParasolDrillEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    Barrier::SetValid(obj(), false);
    obj().model().script().start(0x106);
}

StateParasolDrillEnd::~StateParasolDrillEnd() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        obj().model().subAnimControl().setLiftUpRHand(true);
        Barrier::SetValid(obj(), true);
        obj().soundSE()._78.stop();
    }
}

void StateParasolDrillEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateParasolDrillEnd::procMove() {
    Utility::MoveDefaultBrakeNoOnIce(obj());
}

void StateParasolDrillEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
