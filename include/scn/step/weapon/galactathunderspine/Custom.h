#ifndef SCN_STEP_WEAPON_GALACTATHUNDERSPINE_CUSTOM_H
#define SCN_STEP_WEAPON_GALACTATHUNDERSPINE_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactathunderspine {

class Custom;

}}}}  // namespace scn::step::weapon::galactathunderspine

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::galactathunderspine::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace galactathunderspine {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void attack();
};

}}}}  // namespace scn::step::weapon::galactathunderspine

#endif
