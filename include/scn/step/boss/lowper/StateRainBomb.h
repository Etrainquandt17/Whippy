#ifndef SCN_STEP_BOSS_LOWPER_STATERAINBOMB_H
#define SCN_STEP_BOSS_LOWPER_STATERAINBOMB_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateRainBomb : public StateBase {
public:
    StateRainBomb(Boss* boss, const hel::math::Vector3& pos, u32 frame, u32 interval, u32 count);
    virtual ~StateRainBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBullet();
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 mCount;
    u32 mFrame;
    u32 mInterval;
    u32 mIntervalFrame;
    u32 mShotCount;
    bool mIsShotEnd;
    bool mIsStarted;
};

}}}}  // namespace scn::step::boss::lowper

#endif
