#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/metalgeneralmissile/Custom.h"

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
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
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
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/rollexp/Custom.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralmissile {

Custom::Custom(Enemy& enemy, bool _1) : CustomBase(enemy), mFallInitPos(), _14(_1), mIsExpSED3(false) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    if (_14) {
        obj().culling().setValid(false);
    }
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseCenter(0.5f, 0.45f, 0.45f));
    return false;
}

bool Custom::onDamaged() {
    if (obj().damageInfo().isValid() && obj().damageInfo().data().mSmashType == 0) {
        obj().deadWithEffect();
        return true;
    }
    return true;
}

bool Custom::onHitPointIsZero() {
    obj().deadWithEffectNoItem();
    return true;
}

bool Custom::reqCustomDeadEffect() {
    reqRollExp();
    return true;
}

void Custom::reqRollExp() {
    hel::math::Vector2 pos = obj().location().pos().getXY() + hel::math::Vector2(obj().charaParam()._4);
    enum Variation { VARIATION_NORMAL, VARIATION_D3 };
    Variation variation = mIsExpSED3 ? VARIATION_D3 : VARIATION_NORMAL;
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), variation, static_cast<ostop::Flag>(8), pos, hel::math::Vector2::ZERO,
                      obj().objColl().owner());
    util::ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        hel::common::DynamicCastToRef<weapon::rollexp::Custom, weapon::ICustom>(weapon->custom())
            .changeAttackType(static_cast<ocoll::AttackType>(0x1de));
    }
    if (mIsExpSED3) {
        obj().comp().permSoundSE().start(0x3cc);
    } else {
        obj().comp().permSoundSE().start(0x3e8);
    }
}

void Custom::setFallInitPos(const hel::math::Vector3& pos) {
    mFallInitPos = pos;
}

const hel::math::Vector3& Custom::getFallInitPos() const {
    return mFallInitPos;
}

void Custom::setIsExpSED3(bool isExpSED3) {
    mIsExpSED3 = isExpSED3;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::metalgeneralmissile
