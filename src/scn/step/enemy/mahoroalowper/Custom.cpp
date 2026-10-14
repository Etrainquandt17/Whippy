#include "scn/step/enemy/mahoroalowper/Custom.h"

#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().captureReceiver().setIsIgnoredNonSuper(true);
    return false;
}

bool Custom::onDamaged() {
    return true;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::mahoroalowper
