#include "scn/step/enemy/dubiorjr/Custom.h"

#include "scn/step/Component.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/dubiorjr/ParamData.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    const ParamData& param = obj().param().dubiorjr();
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x4f2), 0);
    return false;
}

bool Custom::onDamaged() {
    if (obj().damageInfo().isValid() && obj().damageInfo().element() == 3) {
        return false;
    }
    if (obj().captureReceiver().isCaptured()) {
        return false;
    }
    obj().deadWithEffect();
    return true;
}

bool Custom::onHitPointIsZero() {
    return onDamaged();
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x4f3), Utility::GetCenterPos(obj()));
    obj().comp().permSoundSE().start(0x59b);
    return true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::dubiorjr
