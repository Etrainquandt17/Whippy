#include "scn/step/hero/spark/Custom.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/hero/Hero.h"

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

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
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

}
}
}
}
