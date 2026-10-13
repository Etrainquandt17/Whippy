#include "scn/step/weapon/mahoroaneedle/StateHold.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroaneedle/Custom.h"
#include "scn/step/weapon/mahoroaneedle/Param.h"
#include "scn/step/weapon/mahoroaneedle/StateEnd.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

StateHold::StateHold(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().rotCtrl().setValid(false);
    obj().model().reqScript(2);
    const Param::Attack* attacks;
    if (Utility::IsExtra(obj())) {
        attacks = obj().param().mahoroaNeedle()._30;
    } else {
        attacks = obj().param().mahoroaNeedle()._C;
    }
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1FD));
    hel::math::Vector2 dir = custom.getUpDir().getXY();
    dir *= 7.0f;
    for (u32 i = 0; i < 3; i++) {
        obj().objColl().addAttack(0, attacks[i]._8, dir * attacks[i]._4, hel::math::Vector2::ZERO);
    }
}

StateHold::~StateHold() {
    obj().objColl().clearAttack();
}

void StateHold::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().mahoroaNeedle();
    custom.updateRot(2.0f);
    if (mFrame < param._8) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateEnd, Weapon*>(&obj());
    }
}

void StateHold::procMove() {}

void StateHold::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroaneedle
