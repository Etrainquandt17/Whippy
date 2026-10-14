#include "scn/step/hero/parasol/StateParasolShield.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/parasol/Barrier.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

StateParasolShield::StateParasolShield(Hero* hero)
    : StateBase(hero) {
    obj().model().subAnimControl().setLiftUpRHand(false);
    Barrier::SetValid(obj(), false);
    obj().model().script().start(0x104);
    obj().piggyback().setEnableReceive(true);
}

StateParasolShield::~StateParasolShield() {
    if (obj().abilityManager().abilityKind() == ABILITY_KIND_PARASOL) {
        obj().model().subAnimControl().setLiftUpRHand(true);
        Barrier::SetValid(obj(), true);
        obj().soundSE()._78.stop();
    }
}

void StateParasolShield::procAnim() {
    Utility::UpdateMoveTarget(obj());
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateParasolShield::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateParasolShield::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::parasol
