#ifndef SCN_STEP_BOSS_COMMON_STATEDASHEND_H
#define SCN_STEP_BOSS_COMMON_STATEDASHEND_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateDashDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

class StateDashEnd : public StateBase {
public:
    StateDashEnd(Boss* boss, StateDashDesc& desc, unsigned long scriptKind);
    virtual ~StateDashEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateDashDesc& mDesc;
};

}}}}  // namespace scn::step::boss::common

#endif
