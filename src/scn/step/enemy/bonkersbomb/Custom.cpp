#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/bonkersbomb/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/bonkersbomb/ParamData.h"
#include "scn/step/enemy/bonkersbomb/StateShot.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/rollexp/Custom.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;
using util::ObjRefHandle;

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::rollexp::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::weapon::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace bonkersbomb {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    const ParamData::Shape& param =
        obj().size() == 0 ? obj().param().bonkersbomb().mShape : obj().param().bonkersbomb().mShapeBig;
    obj().captureReceiver().setCanCapture(false);
    if (obj().size() != 0) {
        obj().vacuumReceiver().setResistLevel(1);
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1ad));
    } else {
        obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1b3));
    }
    obj().mapColl().changeActorShape(
        mcoll::detail::ShapeDiamondContext::CreateBaseBottom(param.mWidth, param.mHeight, param.mSlant));
    obj().mapColl().setValid(true);
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

bool Custom::onDamaged() {
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        return false;
    }
    obj().deadWithEffect();
    return true;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

bool Custom::reqCustomDeadEffect() {
    reqRollExp();
    return true;
}

void Custom::reqRollExp() {
    Vector2 pos = obj().location().pos().getXY() + Vector2(obj().charaParam()._4);
    enum Variation { VARIATION_NORMAL = 1, VARIATION_BIG = 2 };
    Variation variation = obj().size() == 0 ? VARIATION_NORMAL : VARIATION_BIG;
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), variation, static_cast<ostop::Flag>(4), pos, Vector2::ZERO,
                      obj().objColl().owner());
    ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        weapon::rollexp::Custom& custom =
            DynamicCastToRef<weapon::rollexp::Custom, weapon::ICustom>(weapon->custom());
        if (obj().size() != 0) {
            custom.changeAttackType(static_cast<ocoll::AttackType>(0x1ad));
            obj().comp().permSoundSE().start(0x2cc);
        } else {
            custom.changeAttackType(static_cast<ocoll::AttackType>(0x1b3));
            obj().comp().permSoundSE().start(0x2c8);
        }
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::bonkersbomb
