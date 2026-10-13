#ifndef SCN_STEP_BOSS_LOWPER_STATEBOMBOUTOUTIN_H
#define SCN_STEP_BOSS_LOWPER_STATEBOMBOUTOUTIN_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateBombOutOutIn : public StateBase {
public:
    StateBombOutOutIn(Boss* boss);
    virtual ~StateBombOutOutIn();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBomb();
    u32 mCount;
    f32 mInY;
    f32 mOutY;
    f32 mStartX;
    f32 mGoalX;
    f32 mIntpRate;
    f32 mXRate;
    u32 mPhase;
    f32 mRotH;
};

}}}}  // namespace scn::step::boss::lowper

#endif
