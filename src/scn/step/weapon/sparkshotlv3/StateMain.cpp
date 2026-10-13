#include "scn/step/weapon/sparkshotlv3/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/sparkshotlv3/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace sparkshotlv3 {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().mapColl().setValid(false);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x66));
    obj().objColl().addAttack(0, obj().param().sparkShotLv3()._4);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4FE), 0);
}

void StateMain::procAnim() {
    if (++_8 >= obj().param().sparkShotLv3()._0) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::sparkshotlv3
