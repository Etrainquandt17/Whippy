#include "scn/step/enemy/doubterbomb/Custom.h"

#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace doubterbomb {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    return false;
}

bool Custom::onDamaged() {
    return onHitPointIsZero();
}

bool Custom::onHitPointIsZero() {
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        return false;
    }
    reqExplode();
    obj().dead();
    return true;
}

void Custom::reqExplode() {
    Vector2 pos = Utility::GetCenterPos(obj()).getXY();
    weapon::Desc desc(static_cast<weapon::Kind>(0x2f), 1, static_cast<ostop::Flag>(4), pos, Vector2::ZERO,
                      obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
    if (obj().size() == 0) {
        obj().comp().permSoundSE().start(0x2cb);
    } else {
        obj().comp().permSoundSE().start(0x33e);
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::doubterbomb
