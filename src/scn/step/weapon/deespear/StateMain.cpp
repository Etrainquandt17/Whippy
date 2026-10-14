#include "scn/step/weapon/deespear/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/deespear/Param.h"
#include "scn/step/weapon/deespear/StateReflect.h"
#include "scn/step/weapon/deespear/StateStickObj.h"
#include "scn/step/weapon/deespear/StateStickWall.h"
#include "scn/step/weapon/deespear/StateVanish.h"
#include "scn/step/weapon/deespear/Utility.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().deeSpear();
    f32 sign = obj().target().getSign();
    Utility::Rotate(obj());
    obj().model().reqScript(0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x10E), 0);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x14D));
    obj().objColl().setAttackCenter(0, Vector2(-2.0f * sign, 0.0f));
    obj().objColl().addAttack(0, param._4, Vector2(sign * param._8, param._C));
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    Utility::Rotate(obj());
    if (++_8 == obj().param().deeSpear()._0) {
        obj().model().reqScript(1);
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().deeSpear();
    obj().move().airDecelFall(param._10, param._14);
}

void StateMain::procConstraint() {
    if (_8 > 1 && weapon::Utility::PenetrationWeaponMapCollHit(obj())) {
        f32 rot = obj().model().rotCtrl().getRotV();
        if (static_cast<s32>(obj().variation()) == 1) {
            obj().stateChanger().setNextState<StateVanish, Weapon*, f32>(objPtr(), rot);
        } else {
            obj().location().setPos(obj().mapColl().intersectPos().toVector3());
            obj().stateChanger().setNextState<StateStickWall, Weapon*, f32>(objPtr(), rot);
        }
    }
}

void StateMain::procFixPos() {
    if (obj().objColl().attack().isCollide()) {
        if (obj().objColl().attack().getCollidedHitResistLv() >= 6) {
            obj().stateChanger().setNextState<StateReflect, Weapon*>(objPtr());
        } else if (obj().objColl().attack().getCollidedHitResistLv() == 3) {
            f32 rot = obj().model().rotCtrl().getRotV();
            obj().stateChanger().setNextState<StateStickObj, Weapon*, f32>(objPtr(), rot);
        }
    }
}

void StateMain::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::deespear
