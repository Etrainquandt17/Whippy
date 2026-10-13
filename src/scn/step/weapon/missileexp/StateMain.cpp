#include "scn/step/weapon/missileexp/StateMain.h"

#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/missileexp/Param.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace missileexp {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    const Param& param = obj().param().missileExp();
    obj().effect().warp().requestP(static_cast<effect::Kind>(0x130), obj().location().pos(), obj().variation() == 1 ? param._C : 1.0f);
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x47F), obj().location().pos(), obj().variation() == 1 ? param._C : 1.0f);
    obj().soundSE().start(0x50E);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
}

void StateMain::procAnim() {
    const Param& param = obj().param().missileExp();
    mFrame++;
    if (mFrame == 1) {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x243));
        obj().objColl().addAttack(0, param._8);
    }
    if (mFrame == param._4) {
        obj().objColl().clearAttack();
    }
    if (mFrame >= param._0) {
        obj().dead();
    }
}

}
}
}
}
