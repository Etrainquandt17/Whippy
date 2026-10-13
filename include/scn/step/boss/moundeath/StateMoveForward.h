#ifndef SCN_STEP_BOSS_MOUNDEATH_STATEMOVEFORWARD_H
#define SCN_STEP_BOSS_MOUNDEATH_STATEMOVEFORWARD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

class StateMoveForward : public StateBase {
public:
    StateMoveForward(Boss* boss);
    virtual ~StateMoveForward();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::boss::moundeath

#endif
