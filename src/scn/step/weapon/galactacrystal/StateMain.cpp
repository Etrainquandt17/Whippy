#include "scn/step/weapon/galactacrystal/StateMain.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactacrystal {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().initRotH(0.0f);
    obj().mapColl().setValid(false);
}

void StateMain::procAnim() {}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}
}
}
}
