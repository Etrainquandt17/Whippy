#include "scn/step/weapon/mahoroawarpneedle/StateEnd.h"

#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarpneedle {

StateEnd::StateEnd(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(2);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x435), 0);
    obj().soundSE().start(0x409);
}

StateEnd::~StateEnd() {
    obj().effect().normal().release();
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
