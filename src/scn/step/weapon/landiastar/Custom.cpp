#include "scn/step/weapon/landiastar/Custom.h"

#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiastar/StateMain.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiastar {

Custom::Custom(Weapon& weapon) : CustomBase(weapon) {}

bool Custom::onInit() {
    obj().model().reqScript(0);
    obj().culling().setValid(false);
    obj().setVisibility(false);
    obj().mapColl().setValid(false);
    return false;
}

void Custom::reqStart(hel::math::Vector2 pos, hel::math::Vector2 velocity, Variation variation) {
    obj().location().setPos(pos.toVector3());
    obj().move().setVelocity(velocity.toVector3());
    obj().model().updateMtx();
    obj().stateChanger().setNextState<StateMain, Weapon*, Variation>(&obj(), variation);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::landiastar
