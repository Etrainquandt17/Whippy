#include "scn/step/weapon/roahstar/StateShot.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/roahstar/Custom.h"
#include "scn/step/weapon/roahstar/Param.h"

using hel::common::DynamicCast;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace roahstar {

StateShot::StateShot(Weapon* weapon) : StateBase(weapon), _8(0) {
    const Param& param = obj().param().roahStar();
    obj().setVisibility(true);
    if (Utility::IsExtra(obj())) {
        obj().model().setBaseScale(Vector3::ALL_ONE * param._10);
    }
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1F5));
    if (Utility::IsExtra(obj())) {
        obj().objColl().addAttack(0, param._4);
    } else {
        obj().objColl().addAttack(0, param._0);
    }
}

void StateShot::procAnim() {}

void StateShot::procMove() {
    if (obj().isVisible()) {
        const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Zero();
        obj().move().decel(decel);
    }
}

void StateShot::procFixPos() {
    if (obj().isVisible() && Utility::CheckShootingCulling(obj())) {
        DynamicCast<Custom*, ICustom>(obj().custom())->setInvisible();
    }
}

}}}}  // namespace scn::step::weapon::roahstar
