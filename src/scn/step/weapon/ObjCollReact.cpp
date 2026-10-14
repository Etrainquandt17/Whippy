#include "scn/step/weapon/ObjCollReact.h"

#include "ocoll/Attack.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/ocoll/HitResistLv.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

ObjCollReact::ObjCollReact(Weapon& weapon) : mObj(weapon) {}

bool ObjCollReact::procObjCollReact() {
    chara::ObjCollLite& objColl = mObj.objColl();
    if (objColl.attack().isCollide() && objColl.attack().getCollidedHitResistLv() <= ocoll::HIT_RESIST_LV_REPEL) {
        mObj.hitStop().set(objColl.attack().getCollidedHitStopFrame());
    }
    if (objColl.attack().isCollideGimmick()) {
        mObj.comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
        mObj.hitStop().set(6);
    }
    return false;
}

}}}  // namespace scn::step::weapon
