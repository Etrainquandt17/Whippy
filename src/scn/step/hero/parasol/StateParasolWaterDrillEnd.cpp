#include "scn/step/hero/parasol/StateParasolWaterDrillEnd.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/common/StateWaterFloat.h"
#include "scn/step/hero/parasol/Barrier.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

StateParasolWaterDrillEnd::StateParasolWaterDrillEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    Barrier::SetValid(obj(), false);
    if (obj().water().isOnSurface()) {
        obj().stateChecker().setFloat(true);
    }
    obj().model().script().start(0x106);
}

StateParasolWaterDrillEnd::~StateParasolWaterDrillEnd() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        obj().model().subAnimControl().setLiftUpRHand(true);
        Barrier::SetValid(obj(), true);
        obj().soundSE()._78.stop();
    }
}

void StateParasolWaterDrillEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        if (obj().water().isOnSurface()) {
            obj().stateChanger().setNextState<common::StateWaterFloat, Hero*>(objPtr());
        } else {
            Utility::ChangeStateWaitOrFall(obj());
        }
    }
}

void StateParasolWaterDrillEnd::procMove() {
    if (obj().water().isOnSurface()) {
        obj().move().decel(gobj::MoveParamDecel::Zero());
    } else {
        Utility::MoveDefaultBrake(obj());
    }
}

void StateParasolWaterDrillEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::parasol
