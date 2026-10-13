#include "scn/step/weapon/fattybuffercannonsplash/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace fattybuffercannonsplash {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    if (obj().move().velocity().x < 0.0f) {
        obj().target().setIsRightDir(false);
    } else {
        obj().target().setIsRightDir(true);
    }
    obj().move().resetVelocity();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x13B), 0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {}

}}}}  // namespace scn::step::weapon::fattybuffercannonsplash
