#ifndef SCN_STEP_BOSS_COMMON_STATEJUMPATTACKSTART_H
#define SCN_STEP_BOSS_COMMON_STATEJUMPATTACKSTART_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateJumpAttackDesc.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class StateJumpAttackStart : public StateBase {
public:
    StateJumpAttackStart(Boss* boss, StateJumpAttackDesc& desc, unsigned long scriptKind0, unsigned long scriptKind1);
    virtual ~StateJumpAttackStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mScriptKind;
    StateJumpAttackDesc& mDesc;
};

}}}}  // namespace scn::step::boss::common

#endif
