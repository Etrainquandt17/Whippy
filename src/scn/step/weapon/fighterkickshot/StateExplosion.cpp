#include "scn/step/weapon/fighterkickshot/StateExplosion.h"

#include "gobj/Move.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/fighterkickshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterkickshot {

StateExplosion::StateExplosion(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xF3));
    obj().objColl().clearAttack();
    obj().objColl().addAttack(0, obj().param().fighterKickShot()._C);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x167), 0);
    obj().move().resetVelocity();
}

StateExplosion::~StateExplosion() {}

void StateExplosion::procAnim() {
    if (++_8 >= obj().param().fighterKickShot()._10) {
        obj().dead();
    }
}

void StateExplosion::procMove() {}

void StateExplosion::procFixPos() {}

void StateExplosion::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::fighterkickshot
