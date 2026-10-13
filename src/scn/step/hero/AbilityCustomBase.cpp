#include "scn/step/hero/AbilityCustomBase.h"

namespace hel {
namespace common {

// TODO: the instance of the general template that hero/AbilityCustomBaseInfo.h makes. This unit calls it and
// does not hold one, and how the original arranged that is not known.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::hero::AbilityCustomBase>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace hero {

AbilityCustomBase::AbilityCustomBase(Hero& hero) : mHero(hero) {}

AbilityCustomBase::~AbilityCustomBase() {}

const hel::common::RuntimeTypeInfo& AbilityCustomBase::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<AbilityCustomBase>();
}

}}}  // namespace scn::step::hero
