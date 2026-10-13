#include "scn/step/hero/damage/StateSpine.h"
#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/DamageFlash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

StateSpine::StateSpine(Hero* hero)
    : StateBase(hero) {
    obj().footState().setAir();
    obj().model().script().start(0x49);
    obj().comp().permEffect().powerful().requestP(static_cast<effect::Kind>(0xD8),
                                                  obj().location().pos() + hel::math::Vector3(0.0f, 0.5f, 0.0f));
    hel::math::Vector3 velocity = hel::math::Vector3::BASIS_X;
    f32 angle = 60.0f;
    angle += 10.0f * app::Random::RandAF();
    velocity.rotate(hel::math::Vector3::BASIS_Z, 0.017453292f * angle);
    velocity.x *= -1.0f * obj().target().getSign();
    velocity *= 0.125f;
    obj().move().setVelocity(velocity);
    obj().invincible().setPerm();
    obj().damageFlash().set(static_cast<ocoll::Element>(0));
    obj().soundSE()._4.start(0x2A1);
}

StateSpine::~StateSpine() {
    obj().model().modelRotCtrl().setRotV(0.0f);
    obj().model().modelRotCtrl().setRotH(0.0f);
    obj().damageFlash().unset();
    obj().invincible().set(120);
}

void StateSpine::procAnim() {
    if (obj().model().isAllEnd()) {
        hero::Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateSpine::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), obj().param().common()._90);
}

void StateSpine::procFixPos() {
}

}}}}  // namespace scn::step::hero::damage
