#include "scn/step/weapon/waterbulletwarp/StateMain.h"

#include "scn/step/chara/Model.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace waterbulletwarp {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().model().reqScript(0);
    obj().model().setDrawLayerForce(static_cast<core::DrawLayerKind>(2));
}

StateMain::~StateMain() {}

}}}}  // namespace scn::step::weapon::waterbulletwarp
