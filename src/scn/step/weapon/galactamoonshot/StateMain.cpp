#include "scn/step/weapon/galactamoonshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactamoonshot/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactamoonshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().galactaMoonShot();
    obj().target().setIsRightDir(obj().move().velocity().x > 0.0f);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x21E));
    obj().objColl().addAttack(0, param._0, hel::math::Vector2(param._4 * obj().target().getSign(), 0.0f));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x19C), 0, param._8);
    obj().soundSE().start(0x38F);
}

void StateMain::procAnim() {}

void StateMain::procMove() {
    const Param& param = obj().param().galactaMoonShot();
    if (obj().variation() == 1) {
        f32 speed = obj().move().velocity().y;
        speed += param._C;
        obj().move().setSpeedV(hel::math::Math::LimitMax(speed, param._10));
    }
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::galactamoonshot
