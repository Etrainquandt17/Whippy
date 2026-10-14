#include "scn/step/weapon/CustomBase.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& CustomBase::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<CustomBase>();
}

}}}  // namespace scn::step::weapon
