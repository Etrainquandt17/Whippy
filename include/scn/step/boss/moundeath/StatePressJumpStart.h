#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEPRESSJUMPSTART_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEPRESSJUMPSTART_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/moundeath/ScriptKind.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StatePressJumpStart : public StateBase {
public:
    StatePressJumpStart(Boss* boss, JumpKind kind);
    virtual ~StatePressJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    JumpKind mKind;
};

}}}}  // namespace scn::step::boss::moundeath

#endif
