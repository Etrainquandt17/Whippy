#ifndef SCN_STEP_WEAPON_LANDIASINGLEFIREBALL_CUSTOM_H
#define SCN_STEP_WEAPON_LANDIASINGLEFIREBALL_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglefireball {

class Custom;

}}}}  // namespace scn::step::weapon::landiasinglefireball

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::landiasinglefireball::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglefireball {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
};

}}}}  // namespace scn::step::weapon::landiasinglefireball

#endif
