#include "scn/step/weapon/combinationdededebomber/StateExplosion.h"

#include "gobj/Move.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/combinationdededebomber/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdededebomber {

StateExplosion::StateExplosion(Weapon* weapon) : StateBase(weapon), _8(0), _C(0) {
    _C = obj().variation();
    obj().objColl().setAttackType(attackType());
    obj().objColl().clearAttack();
    obj().objColl().addAttack(0, attackRadius());
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0xFB), obj().location().pos());
    obj().move().resetVelocity();
}

StateExplosion::~StateExplosion() {}

void StateExplosion::procAnim() {
    if (++_8 >= obj().param().combinationDededeBomber()._34) {
        obj().dead();
    }
}

void StateExplosion::procMove() {}

void StateExplosion::procFixPos() {}

void StateExplosion::procObjCollReact() {}

f32 StateExplosion::attackRadius() const {
    const Param& param = obj().param().combinationDededeBomber();
    switch (_C) {
    case 0:
        return param._28;
    case 1:
        return param._2C;
    case 2:
        return param._30;
    default:
        return param._28;
    }
}

const ocoll::AttackType& StateExplosion::attackType() const {
    switch (_C) {
    case 0:
        return static_cast<ocoll::AttackType>(0x19);
    case 1:
        return static_cast<ocoll::AttackType>(0x1A);
    case 2:
        return static_cast<ocoll::AttackType>(0x1B);
    default:
        return static_cast<ocoll::AttackType>(0x19);
    }
}

}
}
}
}
