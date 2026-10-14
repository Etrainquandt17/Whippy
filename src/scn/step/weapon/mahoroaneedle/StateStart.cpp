#include "scn/step/weapon/mahoroaneedle/StateStart.h"

#include "gobj/Anim.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroaneedle/Custom.h"
#include "scn/step/weapon/mahoroaneedle/Param.h"
#include "scn/step/weapon/mahoroaneedle/StateHold.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

StateStart::StateStart(Weapon* weapon) : StateBase(weapon) {
    obj().model().rotCtrl().setValid(false);
    obj().model().reqScript(1);
    obj().effect().normal().requestN(static_cast<effect::Kind>(obj().kind() == 0x4E ? 0x42C : 0x3EA), 0);
    obj().effect().normal().requestN(
        static_cast<effect::Kind>(obj().kind() == 0x4E ? 0x42A : (Utility::IsExtra(obj()) ? 0x3D2 : 0x3E8)), 0
    );
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1FD));
}

StateStart::~StateStart() {
    obj().objColl().clearAttack();
}

void StateStart::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    updateAttack();
    custom.updateRot(10.0f);
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateHold, Weapon*>(&obj());
    }
}

void StateStart::procMove() {}

void StateStart::procFixPos() {}

void StateStart::updateAttack() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param::Attack* attacks;
    if (Utility::IsExtra(obj())) {
        attacks = obj().param().mahoroaNeedle()._30;
    } else {
        attacks = obj().param().mahoroaNeedle()._C;
    }
    obj().objColl().clearAttack();
    f32 total = obj().model().anim().totalFrame();
    f32 rate = obj().model().anim().frame() / total;
    f32 cos = Math::CosDegF(90.0f * rate);
    f32 length = 7.0f * (1.0f - cos);
    Vector2 dir = custom.getUpDir().getXY();
    dir *= length;
    for (u32 i = 0; i < 3; i++) {
        if (rate > attacks[i]._0) {
            obj().objColl().addAttack(0, attacks[i]._8, dir * attacks[i]._4, Vector2::ZERO);
        }
    }
}

}}}}  // namespace scn::step::weapon::mahoroaneedle
