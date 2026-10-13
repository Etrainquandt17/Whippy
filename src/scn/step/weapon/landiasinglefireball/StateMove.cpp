#include "scn/step/weapon/landiasinglefireball/StateMove.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiasinglefireball/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglefireball {

StateMove::StateMove(Weapon* weapon) : StateBase(weapon) {
    const Param& param = obj().param().landiaSingleFireBall();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x20F));
    obj().objColl().addAttack(0, param._0);
    obj().move().resetVelocity();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x366), 0);
}

void StateMove::procAnim() {}

void StateMove::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMove::procFixPos() {}

}
}
}
}
