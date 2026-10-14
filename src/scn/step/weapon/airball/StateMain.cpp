#include "scn/step/weapon/airball/StateMain.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/airball/Param.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace airball {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(false) {
    const Param& param = obj().param().airBall();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(5));
    f32 sign = obj().target().getSign();
    obj().objColl().addAttack(
        0, param._4, Vector2(sign * param._C, param._10), Vector2(sign * param._8, param._10));
    obj().model().reqScript(0);
}

void StateMain::procAnim() {
    if (_C) {
        obj().dead();
    } else {
        _8++;
        if (obj().param().airBall()._0 <= _8) {
            dead();
        }
    }
}

void StateMain::procMove() {
    obj().move().airAccelFall(obj().target().isRightDir(), obj().param().airBall()._14, obj().param().airBall()._20);
}

void StateMain::procFixPos() {
    if (obj().water().isInWater()) {
        dead();
    } else if (obj().mapColl().result().isDead()) {
        dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide() || obj().objColl().attack().isCollideGimmick() || obj().mapColl().isHit()) {
        dead();
    }
}

void StateMain::dead() {
    if (!_C) {
        _C = true;
        obj().comp().permEffect().normal().requestPD(static_cast<effect::Kind>(0x5E), obj().location().pos(), obj().target().getDirection3());
    }
}

}}}}  // namespace scn::step::weapon::airball
