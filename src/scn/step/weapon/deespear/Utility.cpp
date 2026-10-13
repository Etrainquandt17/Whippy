#include "scn/step/weapon/deespear/Utility.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

void Utility::Rotate(Weapon& weapon) {
    f32 rot = -(57.29578f * weapon.move().velocity().getXY().signedAngle(hel::math::Vector2::BASIS_X));
    if (!weapon.target().isRightDir()) {
        rot += 180.0f;
    }
    weapon.model().rotCtrl().setRotV(rot);
}

void Utility::Vanish(Weapon& weapon) {
    if (!weapon.isDead()) {
        weapon.model().setVisibility(false);
        weapon.objColl().clearAttack();
        weapon.effect().normal().requestN(static_cast<effect::Kind>(0x5BB), 0);
    }
}

}
}
}
}
