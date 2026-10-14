#include "scn/step/weapon/fattybufferwatercannon/StateMain.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace fattybufferwatercannon {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    if (obj().move().velocity().x < 0.0f) {
        obj().target().setIsRightDir(false);
    } else {
        obj().target().setIsRightDir(true);
    }
    obj().move().resetVelocity();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x139), 0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {}

}}}}  // namespace scn::step::weapon::fattybufferwatercannon
