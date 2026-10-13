#include "scn/step/weapon/mahoroablackholebg/StateMain.h"

#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackholebg {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    hel::math::Vector3 pos = obj().location().pos();
    pos.z = 5.0f;
    obj().location().setPos(pos);
    obj().model().setDrawLayerForce(static_cast<core::DrawLayerKind>(8));
    obj().model().reqScript(0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroablackholebg
