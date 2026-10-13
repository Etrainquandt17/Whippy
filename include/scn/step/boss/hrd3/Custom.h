#ifndef SCN_STEP_BOSS_HRD3_CUSTOM_H
#define SCN_STEP_BOSS_HRD3_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class Custom;

}}}}  // namespace scn::step::boss::hrd3

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::hrd3::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class CollisionCtrl;
class LandCtrl;
class ShadowCtrl;
class PartsCtrl;
class PilotCtrl;

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Boss& boss);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    CollisionCtrl& collisionCtrl();
    ShadowCtrl& shadowCtrl();
    LandCtrl& landCtrl();
    PilotCtrl& pilotCtrl();
    PartsCtrl& partsCtrl();

private:
    // TODO: members.
    u32 _8[449];
};

}}}}  // namespace scn::step::boss::hrd3

#endif
