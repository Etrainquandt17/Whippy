#include "scn/step/enemy/starman/Custom.h"

#include "scn/step/enemy/Enemy.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace starman {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsHighJumpMode(false) {}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setHighJumpMode(bool isHighJump) {
    mIsHighJumpMode = isHighJump;
}

bool Custom::isHighJumpMode() {
    return mIsHighJumpMode;
}

}}}}  // namespace scn::step::enemy::starman
