#include "scn/step/weapon/lowperblackhole/StateMain.h"

#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace lowperblackhole {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    obj().mapColl().setValid(false);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x3A8), obj().location().pos());
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x3A9), obj().location().pos(), 1.5f);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1C1));
    obj().objColl().addAttack(0, 0.6f);
    obj().soundSE().start(0x55A);
}

void StateMain::procAnim() {}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}
}
}
}
