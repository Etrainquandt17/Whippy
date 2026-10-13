#ifndef SCN_STEP_ENEMY_PIERCE_CUSTOM_H
#define SCN_STEP_ENEMY_PIERCE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

class Custom;

}}}}  // namespace scn::step::enemy::pierce

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::pierce::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    bool isPlayerInAimArea();
    void turnHeroWithTime(u32 time);

private:
    u32 mTurnFrame;
};

}}}}  // namespace scn::step::enemy::pierce

#endif
