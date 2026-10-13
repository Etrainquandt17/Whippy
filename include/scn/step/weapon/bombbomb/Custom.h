#ifndef SCN_STEP_WEAPON_BOMBBOMB_CUSTOM_H
#define SCN_STEP_WEAPON_BOMBBOMB_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

class Custom;

}}}}  // namespace scn::step::weapon::bombbomb

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::bombbomb::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);

private:
    u32 _8[15];
};

}}}}  // namespace scn::step::weapon::bombbomb

#endif
