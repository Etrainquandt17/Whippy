#include "scn/step/hero/superice/Custom.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/hero/Hero.h"

namespace scn {
namespace step {
namespace hero {
namespace superice {

Custom::Custom(Hero& hero)
    : AbilityCustomBase(hero)
    , mSnowBall(hero) {
}

Custom::~Custom() {
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

SnowBall& Custom::snowBall() {
    return mSnowBall;
}

}
}
}
}
