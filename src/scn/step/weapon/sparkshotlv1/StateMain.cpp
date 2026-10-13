#include "scn/step/weapon/sparkshotlv1/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/sparkshotlv1/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace sparkshotlv1 {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x64));
    obj().objColl().addAttack(0, obj().param().sparkShotLv1()._4);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4E5), 0, obj().param().sparkShotLv1()._8);
}

void StateMain::procAnim() {
    if (++_8 >= obj().param().sparkShotLv1()._0) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
    const gobj::MoveParamFall& fall = gobj::MoveParamFall::Zero();
    obj().move().airDecelFall(decel, fall);
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide()) {
        obj().dead();
    }
    if (obj().objColl().attack().isCollideGimmick()) {
        obj().dead();
    }
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}
}
}
}
