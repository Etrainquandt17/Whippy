#include "scn/step/weapon/mahoroafrozenarea/StateMain.h"

#include "hel/geo/Rect.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/core/AreaOperation.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroafrozenarea {

// TODO: an inline function that takes both coordinates by value; where it lives is not known.
inline void t_Trans(hel::geo::Rect& rect, f32 x, f32 y) {
    rect.trans(x, y);
}

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mLifetime(), mAreaId(0) {
    obj().mapColl().setValid(false);
    mLifetime.set(900);
    obj().model().rotCtrl().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x40A), 0);
    hel::geo::Rect rect(0.5f, -0.5f, -1.2f, 1.2f);
    t_Trans(rect, obj().location().pos().x, obj().location().pos().y);
    mAreaId = obj().comp().areaOperation().createFrozenArea(rect);
}

StateMain::~StateMain() {
    obj().comp().areaOperation().removeFrozenArea(mAreaId);
}

void StateMain::procAnim() {
    mLifetime.update();
    if (mLifetime.isDead()) {
        obj().dead();
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}
}
}
}
