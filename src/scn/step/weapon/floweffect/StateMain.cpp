#include "scn/step/weapon/floweffect/StateMain.h"

#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Water.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace floweffect {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().mapColl().setValid(false);
    obj().culling().setValid(false);
    obj().worldCage().setIsValid(false);
    obj().water().setForbidEffect(true);
}

void StateMain::procAnim() {}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::floweffect
