#ifndef SCN_STEP_WEAPON_LANDIABURST_CUSTOM_H
#define SCN_STEP_WEAPON_LANDIABURST_CUSTOM_H

#include "hel/math/Vector2.h"
#include "scn/step/weapon/CustomBase.h"
#include "scn/step/weapon/landiaburst/Variation.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiaburst {

class Custom;

}}}}  // namespace scn::step::weapon::landiaburst

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::landiaburst::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace landiaburst {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void reqStart(hel::math::Vector2 pos, hel::math::Vector2 velocity, Variation variation);
};

}}}}  // namespace scn::step::weapon::landiaburst

#endif
