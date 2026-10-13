#ifndef SCN_STEP_BOSS_GOLIATH_CUSTOM_H
#define SCN_STEP_BOSS_GOLIATH_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class Custom;

}}}}  // namespace scn::step::boss::goliath

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::goliath::Custom>();

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class EnemyCtrl;
class LandCtrl;

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Boss& boss);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    EnemyCtrl& enemyCtrl();
    LandCtrl& landCtrl();

private:
    // TODO: members.
    u32 _8[173];
};

}}}}  // namespace scn::step::boss::goliath

#endif
