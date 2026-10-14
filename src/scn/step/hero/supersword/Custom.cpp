#include "scn/step/hero/supersword/Custom.h"
#include "scn/step/hero/Hero.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

SwordSelector& Custom::swordSelector() {
    return mSwordSelector;
}

}}}}  // namespace scn::step::hero::supersword
