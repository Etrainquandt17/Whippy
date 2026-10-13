#include "scn/step/weapon/fightersmashshot/StateExplosion.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/fightersmashshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace fightersmashshot {

StateExplosion::StateExplosion(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xEA));
    obj().objColl().clearAttack();
    obj().objColl().addAttack(0, obj().param().fighterSmashShot()._C);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x163), 0);
    obj().move().resetVelocity();
}

StateExplosion::~StateExplosion() {}

void StateExplosion::procAnim() {
    if (++_8 >= obj().param().fighterSmashShot()._10) {
        obj().dead();
    }
}

void StateExplosion::procMove() {}

void StateExplosion::procFixPos() {}

void StateExplosion::procObjCollReact() {}

}
}
}
}
