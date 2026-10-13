#ifndef SCN_STEP_ENEMY_STAREFFECT_CUSTOM_H
#define SCN_STEP_ENEMY_STAREFFECT_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

class Custom;

}}}}  // namespace scn::step::enemy::stareffect

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::stareffect::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

    void procAnim();

private:
    u32 _8[3];
};

}}}}  // namespace scn::step::enemy::stareffect

#endif
