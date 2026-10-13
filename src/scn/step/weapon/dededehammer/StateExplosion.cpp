#include "scn/step/weapon/dededehammer/StateExplosion.h"

#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/DarknessLight.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/dededehammer/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace dededehammer {

StateExplosion::StateExplosion(Weapon* weapon) : StateBase(weapon), _8(0) {
    obj().objColl().clearAttack();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x146));
    obj().objColl().addAttack(0, obj().param().dededeHammer()._14);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x103), 0);
    obj().model().setVisibility(false);
    const Param& param = obj().param().dededeHammer();
    obj().comp().objStopManager().requestStopPowerful(param._20);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
    obj().comp().permSoundSE().start(0x20E);
    obj().setDarknessLightVisibility(true);
}

// The original converts and divides at each of the four uses.
#define T_RATE (1.0f - static_cast<f32>(frame) / static_cast<f32>(total))

void StateExplosion::procAnim() {
    _8++;
    if (_8 == obj().param().dededeHammer()._18) {
        obj().objColl().clearAttack();
    }
    if (_8 >= obj().param().dededeHammer()._18) {
        u32 frame = _8 - obj().param().dededeHammer()._18;
        u32 total = obj().param().dededeHammer()._1C - obj().param().dededeHammer()._18;
        f32 scale = 1.5f * T_RATE + T_RATE * (-0.5f * T_RATE * T_RATE);
        if (scale > 0.0f) {
            // TODO: Weapon::darknessLight() returns the sfx class; scn/step/weapon/Weapon.h names a class of its own.
            reinterpret_cast<sfx::DarknessLight&>(obj().darknessLight()).setCustomScale(scale);
        }
    }
    if (_8 == obj().param().dededeHammer()._1C) {
        obj().dead();
    }
}

#undef T_RATE

void StateExplosion::procMove() {}

void StateExplosion::procFixPos() {}

void StateExplosion::procObjCollReact() {}

}
}
}
}
