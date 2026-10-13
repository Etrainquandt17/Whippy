#include "scn/step/hero/common/StateShotAirBall.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/IndiviParam.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateShotAirBall::StateShotAirBall(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x11);
    obj().move().setSpeedV(IndiviUtil::Param(obj())._48);
    obj().model().setFixDir(true);
    obj().water().setForbidChangeState(true);
}

StateShotAirBall::~StateShotAirBall() {
    obj().water().setForbidChangeState(false);
}

void StateShotAirBall::procAnim() {
    mFrame++;
    obj().abilityManager().chkDiscardAbility();
    if (obj().model().scriptTrigger().get(0)) {
        Utility::CreateAirBall(obj(), false);
    }
    if (obj().model().scriptTrigger().get(1)) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateShotAirBall::procMove() {
    Utility::MoveFromKeyState(obj(), IndiviUtil::Param(obj())._4C, obj().param().common()._74,
                              IndiviUtil::Param(obj())._58);
}

void StateShotAirBall::procFixPos() {}

}}}}  // namespace scn::step::hero::common
