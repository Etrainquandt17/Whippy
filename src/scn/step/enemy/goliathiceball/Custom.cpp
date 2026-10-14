#include "scn/step/enemy/goliathiceball/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    if (obj().variation() == 0x176) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x295), 0, Vector3(0.0f, 0.5f, 0.0f), 1.0f);
    }
    return false;
}

bool Custom::onDamaged() {
    if (obj().variation() == 0x176) {
        reqExplode();
        obj().deadWithEffect();
        return true;
    }
    return false;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x287), obj().location().pos());
    obj().comp().permSoundSE().start(0x382);
    return true;
}

void Custom::reqExplode() {
    Vector2 pos = Utility::GetCenterPos(obj()).getXY();
    Vector2 velocity = Vector2::ZERO;
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 1, static_cast<ostop::Flag>(4), pos, velocity, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    obj().comp().permSoundSE().start(0x382);
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::goliathiceball
