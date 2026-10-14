#include "scn/step/weapon/spearspear/Utility.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace spearspear {

void Utility::Rotate(Weapon& weapon) {
    f32 rot = -(57.29578f * weapon.move().velocity().getXY().signedAngle(Vector2::BASIS_X));
    if (!weapon.target().isRightDir()) {
        rot += 180.0f;
    }
    weapon.model().rotCtrl().setRotV(rot);
}

void Utility::Vanish(Weapon& weapon) {
    if (!weapon.isDead()) {
        weapon.model().setVisibility(false);
        weapon.objColl().clearAttack();
#ifdef VERSION_SUKK01
        weapon.effect().normal().requestN(static_cast<effect::Kind>(0x63A), 0);
#else
        weapon.effect().normal().requestN(static_cast<effect::Kind>(0x639), 0);
#endif
    }
}

}}}}  // namespace scn::step::weapon::spearspear
