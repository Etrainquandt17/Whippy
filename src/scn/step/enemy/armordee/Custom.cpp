#include "scn/step/enemy/armordee/Custom.h"

#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/waddledee/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace armordee {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {
    obj().captureReceiver().setCanCapture(false);
}

bool Custom::onHitPointIsZero() {
    if (obj().variation() == 0x16d) {
        return waddledee::Utility::CommonBehaviorOnHitPointIsZero(obj(), true, static_cast<map::BinEnemyVariation>(0x164));
    } else if (obj().kind() == 8) {
        return waddledee::Utility::CommonBehaviorOnHitPointIsZero(obj(), true, obj().variation());
    }
    return waddledee::Utility::CommonBehaviorOnHitPointIsZero(obj(), false, obj().variation());
}

f32 Custom::getFrameRate() {
    switch (static_cast<u32>(obj().level())) {
    case 0:
        return 1.0f;
    case 1:
        return 1.5f;
    case 2:
        return 2.0f;
    default:
        return 3.0f;
    }
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::armordee
