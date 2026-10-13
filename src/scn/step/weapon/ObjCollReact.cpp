#include "scn/step/weapon/ObjCollReact.h"

#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

ObjCollReact::ObjCollReact(Weapon& weapon) : mObj(weapon) {}

bool ObjCollReact::procObjCollReact() {
    chara::ObjCollLite& objColl = mObj.objColl();
    if (objColl.attack().isCollide() && objColl.attack().getCollidedHitResistLv() <= 4) {
        mObj.hitStop().set(objColl.attack().getCollidedHitStopFrame());
    }
    if (objColl.attack().isCollideGimmick()) {
        mObj.comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
        mObj.hitStop().set(6);
    }
    return false;
}

}
}
}
