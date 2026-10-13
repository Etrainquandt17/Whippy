#include "scn/step/weapon/fightersmashshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/fightersmashshot/Param.h"
#include "scn/step/weapon/fightersmashshot/StateExplosion.h"

namespace scn {
namespace step {
namespace weapon {
namespace fightersmashshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xE9));
    obj().objColl().addAttack(0, obj().param().fighterSmashShot()._0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x5CA), 0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x162), 0);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    if (++_8 >= obj().param().fighterSmashShot()._4) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x164), 0);
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().airDecelFall(obj().param().fighterSmashShot()._8, gobj::MoveParamFall::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (Utility::PenetrationWeaponMapCollHit(obj())) {
        obj().stateChanger().setNextState<StateExplosion, Weapon*>(objPtr());
    }
}

}
}
}
}
