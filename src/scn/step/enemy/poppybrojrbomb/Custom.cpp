#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/poppybrojrbomb/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/poppybrojrbomb/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/rollexp/Custom.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojrbomb {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    return false;
}

bool Custom::onDamaged() {
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        obj().model().unsetCustomMtx();
        return false;
    }
    obj().comp().permSoundSE().start(0x2cf);
    weapon::Desc desc;
    desc.mKind = static_cast<weapon::Kind>(0x2f);
    desc.mVariation = 1;
    desc.mFlag = static_cast<ostop::Flag>(4);
    desc.mPos = desc._14 =
        obj().location().pos().getXY() + hel::math::Vector2(0.0f, obj().param().poppybrojrbomb().mExplosionOffsetY);
    desc._1c = hel::math::Vector2(0.0f, 0.0f);
    desc.mOwner = &obj().objColl().owner();
    util::ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        hel::common::DynamicCastToRef<weapon::rollexp::Custom, weapon::ICustom>(weapon->custom())
            .changeAttackType(static_cast<ocoll::AttackType>(0x242));
    }
    obj().dead();
    return false;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

bool Custom::onInWater() {
    obj().effect().normal().release();
    obj().model().rotCtrl().setValid(false);
    obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(&obj());
    return true;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::poppybrojrbomb
