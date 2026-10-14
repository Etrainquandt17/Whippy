#include "scn/step/weapon/landiaburst/Custom.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/landiaburst/StateMain.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace landiaburst {

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

void Custom::reqStart(Vector2 pos, Vector2 velocity, Variation variation) {
    obj().location().setPos(pos.toVector3());
    obj().move().setVelocity(velocity.toVector3());
    obj().model().updateMtx();
    obj().stateChanger().setNextState<StateMain, Weapon*, Variation>(&obj(), variation);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::weapon::landiaburst
