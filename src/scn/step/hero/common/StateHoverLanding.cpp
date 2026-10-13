#include "scn/step/hero/common/StateHoverLanding.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

bool StateHoverLanding::TryToChangeState(Hero* hero) {
    if (hero->mapColl().result().mIsHitFloor) {
        hero->stateChanger().setNextState<StateHoverLanding, Hero*>(hero);
        return true;
    }
    return false;
}

StateHoverLanding::StateHoverLanding(Hero* hero)
    : StateBase(hero) {
    obj().footState().setGround();
    obj().model().script().start(0x10);
}

StateHoverLanding::~StateHoverLanding() {}

void StateHoverLanding::procAnim() {
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().scriptTrigger().get(0)) {
        Utility::CreateAirBall(obj(), false);
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateHoverLanding::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateHoverLanding::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
    }
}

}}}}  // namespace scn::step::hero::common
