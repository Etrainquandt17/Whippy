#include "scn/step/weapon/mahoroablackhole/StateEnd.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

StateEnd::StateEnd(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(2);
}

StateEnd::~StateEnd() {
    obj().effect().warp().release();
}

void StateEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().dead();
    }
}

void StateEnd::procMove() {}

void StateEnd::procFixPos() {}

}
}
}
}
