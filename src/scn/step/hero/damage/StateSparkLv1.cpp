#include "scn/step/hero/damage/StateSparkLv1.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/damage/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateSparkLv1::StateSparkLv1(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0x49);
    Utility::InitTarget(obj());
    Utility::InitVelocity(obj());
    obj().invincible().setPerm();
    obj().effect()._58.requestN(static_cast<effect::Kind>(0xE0), 1);
    obj().damageFlash().set(static_cast<ocoll::Element>(4));
}

StateSparkLv1::~StateSparkLv1() {
    obj().model().modelRotCtrl().setRotV(0.0f);
    obj().model().modelRotCtrl().setRotH(0.0f);
    obj().damageFlash().unset();
    obj().invincible().set(120);
}

void StateSparkLv1::procAnim() {
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSparkLv1::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), obj().param().common()._90);
}

void StateSparkLv1::procFixPos() {}

}
}
}
}
