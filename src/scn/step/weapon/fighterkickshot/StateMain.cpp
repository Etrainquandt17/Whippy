#include "scn/step/weapon/fighterkickshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/fighterkickshot/Param.h"
#include "scn/step/weapon/fighterkickshot/StateExplosion.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterkickshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xF2));
    obj().objColl().addAttack(0, obj().param().fighterKickShot()._0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x5C4), 0);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x166), 0);
}

StateMain::~StateMain() {
    obj().effect().normal().release();
}

void StateMain::procAnim() {
    if (++_8 >= obj().param().fighterKickShot()._4) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x168), 0);
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().airDecelFall(obj().param().fighterKickShot()._8, gobj::MoveParamFall::Zero());
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
