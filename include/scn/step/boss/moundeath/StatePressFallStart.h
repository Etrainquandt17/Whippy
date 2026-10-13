#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEPRESSFALLSTART_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEPRESSFALLSTART_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StatePressFallStart : public StateBase {
public:
    StatePressFallStart(Boss* boss, JumpKind kind);
    virtual ~StatePressFallStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    JumpKind mKind;
    u32 mCount;
    u32 mFrame;
};

}}}}  // namespace scn::step::boss::moundeath

#endif
