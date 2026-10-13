#ifndef SCN_STEP_WEAPON_WATERUNDERWATER_CUSTOM_H
#define SCN_STEP_WEAPON_WATERUNDERWATER_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace waterunderwater {

class Custom;

}}}}  // namespace scn::step::weapon::waterunderwater

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::waterunderwater::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace waterunderwater {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
};

}}}}  // namespace scn::step::weapon::waterunderwater

#endif
