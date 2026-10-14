#include "scn/step/hero/tornado/StateChargeAttack.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Landing.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/TornadoParam.h"
#include "scn/step/hero/Utility.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace tornado {

StateChargeAttack::StateChargeAttack(Hero* hero)
    : StateBase(hero)
    , mIsStart(true)
    , mIsEnd(false) {
    obj().model().setAttackNoRenew();
    obj().model().script().start(0x12A);
    obj().invincible().setPerm();
    obj().landing().setValidAir(true);
}

StateChargeAttack::~StateChargeAttack() {
    obj().landing().setValidAir(false);
    if (!mIsEnd) {
        obj().effect()._8.releaseAndVanish();
        obj().effect()._58.releaseAndVanish();
        obj().effect()._80.releaseAndVanish();
    }
}

void StateChargeAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        const TornadoParam& param = obj().param().tornado();
        obj().abilityManager().setActionInterval(param._7C);
        Utility::ChangeStateWaitOrFall(obj());
        mIsEnd = true;
        return;
    }
    if (obj().model().scriptTrigger().get(0)) {
        obj().invincible().unsetPerm();
        f32 speedH = obj().move().velocity().x / 2.0f;
        f32 speedV = 0.65f * obj().move().velocity().y;
        obj().move().setSpeedH(speedH);
        obj().move().setSpeedV(speedV);
    }
    if (mIsStart && obj().model().scriptTrigger().get(1)) {
        mIsStart = false;
    }
}

void StateChargeAttack::procMove() {
    const TornadoParam& param = obj().param().tornado();
    if (mIsStart) {
        Utility::MoveFromKeyState(obj(), param._EC, param._F8, param._FC);
        return;
    }
    Vector3 velocity = obj().move().velocity();
    if (obj().hid().isHold(8)) {
        velocity.y += param._DC;
    } else if (obj().hid().isHold(4)) {
        velocity.y += param._E0;
    }
    velocity.y = Math::LimitMinMax(velocity.y, param._E8, param._E4);
    obj().move().setVelocity(velocity);
    Utility::MoveFromKeyState(obj(), param._108, param._114, param._118);
}

void StateChargeAttack::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::tornado
