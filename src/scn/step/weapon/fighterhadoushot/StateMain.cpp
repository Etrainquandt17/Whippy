#include "scn/step/weapon/fighterhadoushot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/fighterhadoushot/StateExplosion.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterhadoushot {

StateMain::StateMain(Weapon* weapon, Variation variation) : StateBase(weapon), mVariation(variation), _C(0) {
    ocoll::AttackType attackType = static_cast<ocoll::AttackType>(0xF4);
    if (variation == VARIATION_1) {
        attackType = static_cast<ocoll::AttackType>(0xF5);
    }
    if (variation == VARIATION_2) {
        attackType = static_cast<ocoll::AttackType>(0xF7);
    }
    obj().objColl().setAttackType(attackType);
    obj().objColl().addAttack(0, param()._0);
    f32 scale = 3.5f;
    effect::Kind kind = static_cast<effect::Kind>(0x5C6);
    switch (mVariation) {
    case VARIATION_0:
        kind = static_cast<effect::Kind>(0x5C6);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x14F), 0);
        break;
    case VARIATION_1:
        kind = static_cast<effect::Kind>(0x5C7);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x153), 0);
        break;
    case VARIATION_2:
        kind = static_cast<effect::Kind>(0x5C5);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x158), 0);
        break;
    }
    obj().effect().normal().requestN(kind, 0, scale);
    obj().move().setSpeedH(obj().target().getSign() * param()._4);
}

StateMain::~StateMain() {
    obj().effect().normal().releaseAndVanish();
    obj().objColl().clearAttack();
}

void StateMain::procAnim() {
    if (++_C >= 180) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (Utility::PenetrationWeaponMapCollHit(obj())) {
        explode();
    }
}

void StateMain::explode() {
    Variation variation = mVariation;
    switch (variation) {
    case VARIATION_0:
        obj().effect().normal().releaseAndVanish();
        obj().dead();
        break;
    case VARIATION_1:
    case VARIATION_2:
        obj().stateChanger().setNextState<StateExplosion, Weapon*, Variation>(objPtr(), variation);
        break;
    }
}

const ShotParam& StateMain::param() const {
    const Param& param = obj().param().fighterHadouShot();
    switch (mVariation) {
    case VARIATION_0:
        return param._0;
    case VARIATION_1:
        return param._8;
    case VARIATION_2:
        return param._18;
    default:
        return param._0;
    }
}

}
}
}
}
