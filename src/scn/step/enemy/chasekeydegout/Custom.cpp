#include "scn/step/enemy/chasekeydegout/Custom.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace chasekeydegout {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mIsFirstChase(true) {}

bool Custom::onHitPointIsZero() {
    if (obj().variation() == 0x121 || obj().variation() == 0x147) {
        obj().deleteObjGenerator();
    }
    return false;
}

bool Custom::onDamaged() {
    mIsFirstChase = true;
    return false;
}

void Custom::onProcFixPos() {
    if (!Utility::IsExistKeyCarryingHero(obj())) {
        mIsFirstChase = true;
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

void Custom::setFirstChase(bool isFirstChase) {
    mIsFirstChase = isFirstChase;
}

bool Custom::isFirstChase() const {
    return mIsFirstChase;
}

}}}}  // namespace scn::step::enemy::chasekeydegout
