#include "scn/step/weapon/icecube/StateMain.h"

#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace icecube {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {}

StateMain::~StateMain() {}

void StateMain::procAnim() {}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {}

}}}}  // namespace scn::step::weapon::icecube
