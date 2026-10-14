#include "scn/step/enemy/degout/Custom.h"

#include "scn/step/enemy/Enemy.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace degout {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsChaseFlag(false), mIsFirstChase(false) {}

bool Custom::onInit() {
    return false;
}

bool Custom::onDamaged() {
    mIsFirstChase = true;
    if (obj().variation() == 0x7f) {
        mIsChaseFlag = true;
    }
    return false;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setChaseFlag(bool flag) {
    mIsChaseFlag = flag;
}

bool Custom::isChaseFlag() const {
    return mIsChaseFlag;
}

void Custom::setFirstChase(bool flag) {
    mIsFirstChase = flag;
}

bool Custom::isFirstChase() const {
    return mIsFirstChase;
}

}}}}  // namespace scn::step::enemy::degout
