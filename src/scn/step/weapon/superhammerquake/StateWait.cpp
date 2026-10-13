#include "scn/step/weapon/superhammerquake/StateWait.h"

#include "gobj/Move.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/superhammerquake/StateMain.h"
#include "scn/step/weapon/superhammerquake/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace weapon {
namespace superhammerquake {

StateWait::StateWait(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    obj().move().resetVelocity();
}

void StateWait::procAnim() {
    mFrame++;
    if (mFrame >= Utility::GetParamLevel(obj())._0) {
        obj().stateChanger().setNextState<StateMain, Weapon*>(objPtr());
    }
}

void StateWait::procMove() {}

void StateWait::procFixPos() {}

void StateWait::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::superhammerquake
