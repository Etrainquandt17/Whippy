#include "scn/step/weapon/knucklejoehadou/StateMain.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/knucklejoehadou/Param.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace knucklejoehadou {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(false) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x22F));
    const Param& param = obj().param().knucklejoeHadou();
    f32 sign = obj().target().getSign();
    obj().objColl().addAttack(
        0, param._4, Vector2(sign * param._C, param._10), Vector2(sign * param._8, param._10));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x149), 0);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    if (_C) {
        obj().dead();
    } else {
        _8++;
        if (obj().param().knucklejoeHadou()._0 <= _8) {
            dead();
        }
    }
}

void StateMain::procMove() {
    obj().move().airAccelFall(obj().target().isRightDir(), obj().param().knucklejoeHadou()._14, obj().param().knucklejoeHadou()._20);
}

void StateMain::procFixPos() {
    if (obj().water().isInWater()) {
        dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().mapColl().isHit()) {
        dead();
    }
}

void StateMain::dead() {
    if (_C) {
        return;
    }
    _C = true;
}

}}}}  // namespace scn::step::weapon::knucklejoehadou
