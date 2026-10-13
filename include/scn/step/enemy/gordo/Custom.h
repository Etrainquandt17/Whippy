#ifndef SCN_STEP_ENEMY_GORDO_CUSTOM_H
#define SCN_STEP_ENEMY_GORDO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

class Custom;

}}}}  // namespace scn::step::enemy::gordo

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::gordo::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
};

}}}}  // namespace scn::step::enemy::gordo

#endif
