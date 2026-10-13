#ifndef SCN_STEP_WEAPON_COMOTHREAD_CUSTOM_H
#define SCN_STEP_WEAPON_COMOTHREAD_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace comothread {

class Custom;

}}}}  // namespace scn::step::weapon::comothread

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::comothread::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace weapon {
namespace comothread {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);

private:
    u32 _8[5];
};

}}}}  // namespace scn::step::weapon::comothread

#endif
