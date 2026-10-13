#ifndef SCN_STEP_WEAPON_FATTYBUFFERWATERCANNON_CUSTOM_H
#define SCN_STEP_WEAPON_FATTYBUFFERWATERCANNON_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace fattybufferwatercannon {

class Custom;

}}}}  // namespace scn::step::weapon::fattybufferwatercannon

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::fattybufferwatercannon::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace fattybufferwatercannon {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
};

}}}}  // namespace scn::step::weapon::fattybufferwatercannon

#endif
