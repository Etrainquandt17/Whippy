#include "scn/step/weapon/grandlowpersparkshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Lifetime.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace grandlowpersparkshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mLifetime() {
    mLifetime.set(0x3C);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x2B1), 0);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1DA));
    obj().objColl().addAttack(0, 0.5f);
}

void StateMain::procAnim() {
    mLifetime.update();
    if (mLifetime.isDead()) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::grandlowpersparkshot
