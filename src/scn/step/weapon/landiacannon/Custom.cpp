#include "scn/step/weapon/landiacannon/Custom.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiacannon/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiacannon {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().model().reqScript(0);
    obj().culling().setValid(false);
    obj().target().setIsRightDir(true);
    obj().setVisibility(false);
    obj().mapColl().setValid(false);
    obj().objColl().clearHit();
    return false;
}

void Custom::reqStart(hel::math::Vector2 pos, hel::math::Vector2 velocity) {
    obj().location().setPos(pos.toVector3());
    obj().move().setVelocity(velocity.toVector3());
    obj().model().updateMtx();
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
