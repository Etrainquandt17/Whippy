#include "scn/step/weapon/landiasinglefirerain/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiasinglefirerain/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglefirerain {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().landiaSingleFireRain();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x210));
    obj().objColl().addAttack(0, param._0);
    hel::math::Vector3 velocity = obj().move().velocity();
    velocity *= param._8;
    obj().move().setVelocity(velocity);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x369), 0);
}

void StateMain::procAnim() {
    const Param& param = obj().param().landiaSingleFireRain();
    _8++;
    if (_8 >= param._4) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(obj().param().landiaSingleFireRain()._C);
}

void StateMain::procFixPos() {
    const Param& param = obj().param().landiaSingleFireRain();
    if (obj().mapColl().isHit()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x35F), obj().location().pos());
        if (obj().variation() != 0) {
            hel::math::Vector2 offset(param._10 * obj().target().getSign(), param._14);
            hel::math::Vector2 velocity(param._18 * obj().target().getSign(), param._1C);
            Utility::GenerateStarEffect(obj(), offset, velocity, static_cast<map::BinEnemyVariation>(0x19B));
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + offset.toVector3());
        }
        obj().comp().permSoundSE().start(0x46C);
        obj().dead();
    }
}

}
}
}
}
