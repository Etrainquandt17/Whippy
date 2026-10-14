#include "scn/step/enemy/walky/Custom.h"

#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/walky/ParamData.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace walky {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mSpeed(0.0f), mAnimRate(0.0f) {
    switch (obj().level()) {
    case 0:
        mSpeed = obj().param().walky().mSpeed[0];
        break;
    case 1:
        mSpeed = obj().param().walky().mSpeed[1];
        break;
    default:
        mSpeed = obj().param().walky().mSpeed[2];
        break;
    }
    mAnimRate = mSpeed / 0.04f;
}

bool Custom::onInit() {
    return false;
}

bool Custom::onDamaged() {
    onInit();
    return false;
}

f32 Custom::getSpeed() const {
    return mSpeed;
}

f32 Custom::getAnimRate() const {
    return mAnimRate;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::walky
