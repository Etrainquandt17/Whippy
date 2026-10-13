#include "scn/step/hero/supersword/Custom.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/hero/Hero.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {

Custom::Custom(Hero& hero)
    : AbilityCustomBase(hero)
    , mSwordSelector(hero.comp()) {
}

Custom::~Custom() {
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

SwordSelector& Custom::swordSelector() {
    return mSwordSelector;
}

}}}}  // namespace scn::step::hero::supersword
