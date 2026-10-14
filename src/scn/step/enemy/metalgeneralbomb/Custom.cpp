#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/metalgeneralbomb/Custom.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/CharaParam.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/metalgeneralbomb/StateShot.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/rollexp/Custom.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbomb {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseBottom(0.2f, 0.2f, 0.2f));
    obj().stateChanger().setNextState<StateShot, Enemy*>(&obj());
    return true;
}

bool Custom::onDamaged() {
    obj().deadWithEffect();
    return true;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

bool Custom::reqCustomDeadEffect() {
    reqRollExp(false);
    return true;
}

void Custom::reqRollExp(bool isLanding) {
    Vector2 pos = obj().location().pos().getXY() + Vector2(obj().charaParam()._4);
    enum Variation { VARIATION_NORMAL = 0, VARIATION_LANDING = 2 };
    Variation variation = isLanding ? VARIATION_LANDING : VARIATION_NORMAL;
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), variation, static_cast<ostop::Flag>(8), pos, Vector2::ZERO,
                      obj().objColl().owner());
    ObjRefHandle<weapon::Weapon> weapon = obj().comp().weaponManager().request(desc);
    if (weapon.isAlive()) {
        DynamicCastToRef<weapon::rollexp::Custom, weapon::ICustom>(weapon->custom())
            .changeAttackType(static_cast<ocoll::AttackType>(0x1de));
    }
    obj().comp().permSoundSE().start(0x3f1);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::metalgeneralbomb
