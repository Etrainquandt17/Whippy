#include "scn/step/weapon/beamwaveshot/StateExplosion.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/beamwaveshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace beamwaveshot {

StateExplosion::StateExplosion(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x5C));
    obj().objColl().clearAttack();
    obj().objColl().addAttack(0, obj().param().beamWaveShot()._8);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x41), 0);
    obj().move().resetVelocity();
}

StateExplosion::~StateExplosion() {}

void StateExplosion::procAnim() {
    if (++_8 >= obj().param().beamWaveShot()._C) {
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
