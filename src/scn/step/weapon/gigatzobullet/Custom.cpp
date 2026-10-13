#include "scn/step/weapon/gigatzobullet/Custom.h"

#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/gigatzobullet/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace gigatzobullet {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {
    if (obj().variation() == 1) {
        obj().mapColl().setValid(false);
        obj().objColl().clearAttack();
        obj().objColl().clearHit();
        obj().shadow().setVisibility(false);
    }
}

bool Custom::onInit() {
    obj().stateChanger().setNextState<StateMain, Weapon*>(&obj());
    return true;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
