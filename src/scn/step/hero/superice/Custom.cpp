#include "scn/step/hero/superice/Custom.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/hero/Hero.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

SnowBall& Custom::snowBall() {
    return mSnowBall;
}

}}}}  // namespace scn::step::hero::superice
