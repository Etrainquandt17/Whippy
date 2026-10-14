#include "scn/step/weapon/beamcaptureshot/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/beamcaptureshot/Param.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace beamcaptureshot {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().setValidAttackRumble(true);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x30), 0, Vector3(0.0f, obj().param().beamCaptureShot()._0, 0.0f));
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    if (++_8 >= obj().param().beamCaptureShot()._4) {
        obj().effect().normal().release();
        obj().dead();
    }
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procObjCollReact() {
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::beamcaptureshot
