#ifndef SCN_STEP_WEAPON_ROAHSTAR_CUSTOM_H
#define SCN_STEP_WEAPON_ROAHSTAR_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahstar {

class Custom;

}}}}  // namespace scn::step::weapon::roahstar

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::roahstar::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace roahstar {

// TODO: members and the other functions; the unit is not written yet.
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setInvisible();
};

}}}}  // namespace scn::step::weapon::roahstar

#endif
