#include "scn/step/weapon/lupashot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "ocoll/Attack.h"
#include "ocoll/Hit.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/lupashot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace lupashot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    const Param& param = obj().param().lupaShot();
    obj().model().reqScript(0);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1A9));
    obj().objColl().addAttack(0, param._0);
    obj().objColl().addHit(0, param._4);
    obj().model().setViewOffset(hel::math::Vector3(0.0f, -0.5f, 0.0f));
    hel::math::Vector3 velocity = obj().move().velocity();
    velocity.normalize();
    velocity *= param._8;
    obj().move().setVelocity(velocity);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x3AD), 0);
    obj().culling().setValid(false);
}

void StateMain::procAnim() {}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x3AE), obj().location().pos());
        obj().dead();
    } else if (Utility::CheckShootingCulling(obj())) {
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().hit().isCollide() || obj().objColl().attack().isCollide()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x3AE), obj().location().pos());
        obj().dead();
    }
}

}
}
}
}
