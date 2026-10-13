#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEGLIDE_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEGLIDE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleGlide : public StateBase {
public:
    StateTackleGlide(Boss* boss, u32 frame);
    virtual ~StateTackleGlide();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mFrame;
    f32 mStartY;
    f32 mGoalY;
    f32 mGoalX;
    f32 mStartX;
};

}}}}  // namespace scn::step::boss::lowper

#endif
