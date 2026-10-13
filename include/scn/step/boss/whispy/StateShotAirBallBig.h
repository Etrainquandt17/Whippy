#ifndef SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALLBIG_H
#define SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALLBIG_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/whispy/StateShotAirBallBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateShotAirBallBig : public StateShotAirBallBase {
public:
    StateShotAirBallBig(Boss* boss, u32 count, u32 intervalFirst, u32 interval);
    virtual void reqAirBall();

private:
    void reqAirBallIN(const hel::math::Vector2& offset, const hel::math::Vector2& target);
};

}}}}  // namespace scn::step::boss::whispy

#endif
