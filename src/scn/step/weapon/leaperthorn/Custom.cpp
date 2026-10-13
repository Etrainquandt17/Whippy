#include "scn/step/weapon/leaperthorn/Custom.h"

#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/leaperthorn/Param.h"
#include "scn/step/weapon/leaperthorn/StateMain.h"
#include "std/cmath.h"

namespace scn {
namespace step {
namespace weapon {
namespace leaperthorn {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    const Param& param = obj().param().leaperThorn();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1A9));
    obj().objColl().addAttack(0, param._0);
    obj().objColl().clearHit();
    obj().objColl().attack().setValid(false);
    obj().culling().setValid(false);
    obj().model().setVisibility(false);
    obj().mapColl().setValid(false);
    return false;
}

void Custom::reqStart(hel::math::Vector2 pos, hel::math::Vector2 dir) {
    const Param& param = obj().param().leaperThorn();
    obj().location().setPos(pos.toVector3());
    hel::math::Vector3 velocity = dir.toVector3();
    velocity.normalize();
    velocity *= param._C;
    obj().move().setVelocity(velocity);
    f32 angle = static_cast<f32>(acos(hel::math::Vector2::BASIS_Y.cos(velocity.getXY())));
    if (velocity.x > 0.0f) {
        angle *= -1.0f;
    }
    obj().model().rotCtrl().initRotV(57.29578f * angle);
    obj().objColl().attack().setValid(true);
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
