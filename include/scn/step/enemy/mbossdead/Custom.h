#ifndef SCN_STEP_ENEMY_MBOSSDEAD_CUSTOM_H
#define SCN_STEP_ENEMY_MBOSSDEAD_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mbossdead {

class Custom;

}}}}  // namespace scn::step::enemy::mbossdead

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::mbossdead::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace mbossdead {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

private:
    u32 _8[5];
};

}}}}  // namespace scn::step::enemy::mbossdead

#endif
