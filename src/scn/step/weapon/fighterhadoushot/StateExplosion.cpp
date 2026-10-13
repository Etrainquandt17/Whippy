#include "scn/step/weapon/fighterhadoushot/StateExplosion.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/sfx/DarknessLight.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterhadoushot {

StateExplosion::StateExplosion(Weapon* weapon, Variation variation) : StateBase(weapon), mVariation(variation), _C(0) {
    ocoll::AttackType attackType = static_cast<ocoll::AttackType>(0xF6);
    if (variation == VARIATION_2) {
        attackType = static_cast<ocoll::AttackType>(0xF8);
    }
    obj().objColl().setAttackType(attackType);
    obj().objColl().addAttack(0, param()._0);
    effect::Kind kind = static_cast<effect::Kind>(0x151);
    if (mVariation == VARIATION_2) {
        kind = static_cast<effect::Kind>(0x15A);
    }
    obj().effect().normal().requestN(kind, 0);
    obj().move().resetVelocity();
}

StateExplosion::~StateExplosion() {}

void StateExplosion::procAnim() {
    if (++_C >= param()._4) {
        obj().dead();
    } else if (mVariation == VARIATION_2) {
        f32 t = 1.0f - static_cast<f32>(_C) / static_cast<f32>(param()._4);
        f32 scale = 1.5f * t + t * (-0.5f * t * t);
        if (scale > 0.0f) {
            // TODO: Weapon::darknessLight() returns the sfx class; scn/step/weapon/Weapon.h names a class of its own.
            reinterpret_cast<sfx::DarknessLight&>(obj().darknessLight()).setCustomScale(scale);
        }
    }
}

void StateExplosion::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateExplosion::procFixPos() {}

void StateExplosion::procObjCollReact() {}

const ExplosionParam& StateExplosion::param() const {
    const Param& param = obj().param().fighterHadouShot();
    switch (mVariation) {
    case VARIATION_1:
        return param._10;
    case VARIATION_2:
        return param._20;
    default:
        return param._10;
    }
}

}
}
}
}
