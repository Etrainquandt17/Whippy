#ifndef SCN_STEP_BOSS_COMMON_STATEDASHWALLHIT_H
#define SCN_STEP_BOSS_COMMON_STATEDASHWALLHIT_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateDashDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateDashWallHit : public StateBase {
public:
    StateDashWallHit(Boss* boss, StateDashDesc& desc, unsigned long scriptKind);
    virtual ~StateDashWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateDashDesc& mDesc;
};

}}}}  // namespace scn::step::boss::common

#endif
