#include "scn/step/hero/stone/StateUpper.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

namespace {

inline const StoneParamUpper& param(Hero& hero) {
    return hero.param().stone()._5C;
}

}

bool StateUpper::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20) && hero->hid().isHold(8)) {
        hero->stateChanger().setNextState<StateUpper, Hero*>(hero);
        return true;
    }
    return false;
}

StateUpper::StateUpper(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().model().script().start(0xE2);
    obj().move().resetSpeedV();
}

StateUpper::~StateUpper() {
    obj().abilityManager().setActionInterval(param(obj())._4);
}

void StateUpper::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateUpper::procMove() {
    if (obj().footState().isGround()) {
        hero::Utility::MoveDefaultBrake(obj());
    } else if (mFrame < param(obj())._0) {
        obj().move().airDecelFall(obj().param().common()._74, gobj::MoveParamFall::Create(0.0f, 0.0f, 1.0f));
    } else {
        hero::Utility::MoveDefaultBrake(obj());
    }
}

void StateUpper::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::stone
