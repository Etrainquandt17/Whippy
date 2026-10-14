#include "scn/step/hero/spark/Custom.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/hero/Hero.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace hero {
namespace spark {

Custom::Custom(Hero& hero)
    : AbilityCustomBase(hero)
    , mShakeCharge(hero)
    , mIsAction(false) {
}

Custom::~Custom() {
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

ShakeCharge& Custom::shakeCharge() {
    return mShakeCharge;
}

bool Custom::isAction() const {
    return mIsAction;
}

void Custom::setAction(bool isAction) {
    mIsAction = isAction;
}

}}}}  // namespace scn::step::hero::spark
