#include "scn/step/weapon/mahoroastormeffect/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroastormeffect {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().mapColl().setValid(false);
    obj().model().rotCtrl().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x1D0), 0);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

}
}
}
}
