#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {

CustomBase::CustomBase(Weapon& weapon) : mObj(weapon) {}

Weapon& CustomBase::obj() const {
    return mObj;
}

Weapon& CustomBase::obj() {
    return mObj;
}

bool CustomBase::onInit() {
    return false;
}

void CustomBase::onDead() {}

void CustomBase::reqCustomDeadEffect() {}

const hel::common::RuntimeTypeInfo& CustomBase::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<CustomBase>();
}

}}}  // namespace scn::step::weapon
