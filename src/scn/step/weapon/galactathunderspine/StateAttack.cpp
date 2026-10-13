#include "scn/step/weapon/galactathunderspine/StateAttack.h"

#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactathunderspine {

StateAttack::StateAttack(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x221));
    hel::math::Vector2 start(0.0f, 0.0f);
    hel::math::Vector2 end(0.0f, 8.0f);
    obj().objColl().addAttack(0, 0.2f, start, end);
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x19B), obj().location().pos());
}

void StateAttack::procAnim() {
    if (++mFrame == 15) {
        obj().dead();
    }
}

void StateAttack::procMove() {}

void StateAttack::procFixPos() {}

}}}}  // namespace scn::step::weapon::galactathunderspine
