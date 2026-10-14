#include "scn/step/hero/stone/StateEnd.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/StoneParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/Water.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace hero {
namespace stone {

StateEnd::StateEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0xE1);
    f32 speed = obj().move().velocity().x;
    if (!Math::EqZero(speed)) {
        obj().target().setIsRightDir(speed > 0.0f);
    }
    const StoneParam& param = obj().param().stone();
    obj().move().setSpeedV(obj().water().isInWater() ? param._54 : param._50);
    obj().footState().setAir();
    obj().invincible().set(param._58);
}

StateEnd::~StateEnd() {
    obj().stateChecker().setRun(false);
    obj().stateChecker().setStoneWait(false);
}

void StateEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateEnd::procMove() {
    hero::Utility::MoveDefaultAction(obj());
}

void StateEnd::procFixPos() {
    hero::Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::stone
