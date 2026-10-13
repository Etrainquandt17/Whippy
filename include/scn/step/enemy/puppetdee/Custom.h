#ifndef SCN_STEP_ENEMY_PUPPETDEE_CUSTOM_H
#define SCN_STEP_ENEMY_PUPPETDEE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace puppetdee {

class Custom;

}}}}  // namespace scn::step::enemy::puppetdee

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::puppetdee::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace puppetdee {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
};

}}}}  // namespace scn::step::enemy::puppetdee

#endif
