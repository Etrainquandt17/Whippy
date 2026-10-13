#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/foley/Custom.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
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
#include "scn/step/enemy/foley/ParamData.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/rollexp/Custom.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace foley {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsAttack(false) {}

bool Custom::onInit() {
    if (obj().variation() == 0x69) {
        f32 rot = obj().param().foley().mRotH;
        obj().model().rotCtrl().initRotH(rot);
        obj().model().rotCtrl().setValid(false);
    } else {
        f32 rot = obj().param().foley().mRotHDefault;
        obj().model().rotCtrl().initRotH(rot);
        Utility::SetTargetByDirType(obj());
    }
    obj().objColl().clearBodyColl();
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    scale *= obj().param().foley().mBodyRadius;
    obj().objColl().addBodyColl(4, scale);
    return false;
}

bool Custom::onVacuumReceive() {
    if (mIsAttack) {
        obj().model().model().nodes().at(1).setVisibility(false);
        obj().model().model().nodes().at(2).setVisibility(false);
    }
    return false;
}

bool Custom::onDamaged() {
    if (mIsAttack) {
        obj().model().model().nodes().at(1).setVisibility(false);
        obj().model().model().nodes().at(2).setVisibility(false);
    }
    int smashType = obj().damageInfo().data().mSmashType;
    if (mIsAttack == true && smashType == 0) {
        requestRollExp();
    }
    return false;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

// TODO: the two vectors have their stack slots the other way round in the original (velocity at 8, pos at 0x10).
void Custom::requestRollExp() {
    hel::math::Vector2 velocity(0.0f, 0.0f);
    hel::math::Vector2 pos = obj().location().pos().getXY();
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 1, static_cast<ostop::Flag>(4), pos, velocity, obj().objColl().owner());
    util::ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        hel::common::DynamicCastToRef<weapon::rollexp::Custom, weapon::ICustom>(weapon->custom())
            .changeAttackType(static_cast<ocoll::AttackType>(0x242));
    }
    obj().soundSE().stop();
    obj().comp().permSoundSE().start(0x2cf);
    obj().deadIndependent();
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setAttack(bool isAttack) {
    mIsAttack = isAttack;
}

}}}}  // namespace scn::step::enemy::foley
