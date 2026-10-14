#include "scn/step/hero/AbilityCustomBase.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

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

const RuntimeTypeInfo& AbilityCustomBase::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<AbilityCustomBase>();
}

}}}  // namespace scn::step::hero
