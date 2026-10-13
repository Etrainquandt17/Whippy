#ifndef SCN_STEP_ENEMY_MOPOO_CUSTOM_H
#define SCN_STEP_ENEMY_MOPOO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

class Custom;

}}}}  // namespace scn::step::enemy::mopoo

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::mopoo::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);

    int waitTime() const;
    void setWaitTime(int time);
    bool isVariationGround() const;
    bool isVariationConst() const;

private:
    u32 _8[6];
};

}}}}  // namespace scn::step::enemy::mopoo

#endif
