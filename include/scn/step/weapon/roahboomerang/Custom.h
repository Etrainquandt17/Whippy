#ifndef SCN_STEP_WEAPON_ROAHBOOMERANG_CUSTOM_H
#define SCN_STEP_WEAPON_ROAHBOOMERANG_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahboomerang {

class Custom;

}}}}  // namespace scn::step::weapon::roahboomerang

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::roahboomerang::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace roahboomerang {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual void reqCustomDeadEffect();
};

}}}}  // namespace scn::step::weapon::roahboomerang

#endif
