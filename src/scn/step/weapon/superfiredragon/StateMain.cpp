#include "scn/step/weapon/superfiredragon/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace superfiredragon {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
}

StateMain::~StateMain() {
    obj().effect().normal().releaseAndVanish();
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

}}}}  // namespace scn::step::weapon::superfiredragon
