#include "scn/step/weapon/combinationdeeshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdeeshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().mapColl().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x10B), 2, param()._4);
    f32 radius = param()._0;
    obj().objColl().setAttackType(attackType());
    obj().objColl().addAttack(2, radius);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    _8++;
    if (_8 > obj().param().combinationDeeShot()._18) {
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {}

const LevelParam& StateMain::param() const {
    const Param& param = obj().param().combinationDeeShot();
    switch (static_cast<int>(obj().variation())) {
    case 0:
        return param._0;
    case 1:
        return param._8;
    case 2:
        return param._10;
    default:
        return param._0;
    }
}

const ocoll::AttackType& StateMain::attackType() const {
    switch (static_cast<int>(obj().variation())) {
    case 0:
        return static_cast<ocoll::AttackType>(0x1D);
    case 1:
        return static_cast<ocoll::AttackType>(0x1E);
    case 2:
        return static_cast<ocoll::AttackType>(0x1F);
    default:
        return static_cast<ocoll::AttackType>(0x1D);
    }
}

}
}
}
}
