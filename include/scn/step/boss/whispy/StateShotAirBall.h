#ifndef SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALL_H
#define SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALL_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/whispy/StateShotAirBallBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateShotAirBall : public StateShotAirBallBase {
public:
    StateShotAirBall(Boss* boss, u32 count, u32 intervalFirst, u32 interval);
    virtual void reqAirBall();

private:
    hel::math::Vector2 mTargetPos;
};

}}}}  // namespace scn::step::boss::whispy

#endif
