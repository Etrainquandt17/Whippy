#ifndef SCN_STEP_BOSS_COMMON_STATEDASH_H
#define SCN_STEP_BOSS_COMMON_STATEDASH_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateDashDesc.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class StateDash : public StateBase {
public:
    StateDash(Boss* boss, StateDashDesc& desc, unsigned long scriptKind, unsigned long scriptKindWallHit, unsigned long scriptKindEnd);
    virtual ~StateDash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsDash;
    u32 mScriptKindWallHit;
    u32 mScriptKindEnd;
    StateDashDesc& mDesc;
    f32 mStartX;
};

}}}}  // namespace scn::step::boss::common

#endif
