#ifndef SCN_STEP_WEAPON_METALGENERALPATRIOTFIRE_CUSTOM_H
#define SCN_STEP_WEAPON_METALGENERALPATRIOTFIRE_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralpatriotfire {

class Custom;

}}}}  // namespace scn::step::weapon::metalgeneralpatriotfire

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::metalgeneralpatriotfire::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace metalgeneralpatriotfire {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
};

}}}}  // namespace scn::step::weapon::metalgeneralpatriotfire

#endif
