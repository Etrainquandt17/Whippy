#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEGROUNDPRE_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEGROUNDPRE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleGroundPre : public StateBase {
public:
    StateTackleGroundPre(Boss* boss, u32 frame);
    virtual ~StateTackleGroundPre();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    f32 mY;
    f32 mStartX;
    f32 mGoalX;
};

}}}}  // namespace scn::step::boss::lowper

#endif
