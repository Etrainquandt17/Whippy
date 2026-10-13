#ifndef SCN_STEP_ENEMY_PARASOLDOO_CUSTOM_H
#define SCN_STEP_ENEMY_PARASOLDOO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

class Custom;

}}}}  // namespace scn::step::enemy::parasoldoo

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::parasoldoo::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

    void setReleaseOnLanding();

private:
    u32 _8[6];
};

}}}}  // namespace scn::step::enemy::parasoldoo

#endif
