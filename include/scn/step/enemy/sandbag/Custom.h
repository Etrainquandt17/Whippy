#ifndef SCN_STEP_ENEMY_SANDBAG_CUSTOM_H
#define SCN_STEP_ENEMY_SANDBAG_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sandbag {

class Custom;

}}}}  // namespace scn::step::enemy::sandbag

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::sandbag::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace sandbag {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

private:
    u32 _8[3];
};

}}}}  // namespace scn::step::enemy::sandbag

#endif
