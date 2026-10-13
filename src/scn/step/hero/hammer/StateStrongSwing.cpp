#include "scn/step/hero/hammer/StateStrongSwing.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

bool StateStrongSwing::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->hid().isHold(8) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateStrongSwing, Hero*>(hero);
        return true;
    }
    return false;
}

StateStrongSwing::StateStrongSwing(Hero* hero)
    : StateBase(hero) {
    obj().model().setFixDir(true);
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x133);
}

StateStrongSwing::~StateStrongSwing() {
    obj().model().subAnimControl().setLiftUpRHand(true);
}

void StateStrongSwing::procAnim() {
    if (obj().model().scriptTrigger().get(0)) {
        obj().abilityManager().setCustomDarknessLightSizeKind(static_cast<sfx::DarknessLightSizeKind>(5));
    }
    if (obj().model().scriptTrigger().get(1)) {
        obj().abilityManager().resetCustomDarknessLightSizeKind();
    }
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateStrongSwing::procMove() {
    hero::Utility::MoveDefaultAction(obj());
}

void StateStrongSwing::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::hammer
