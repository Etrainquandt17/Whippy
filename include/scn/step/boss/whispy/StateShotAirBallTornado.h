#ifndef SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALLTORNADO_H
#define SCN_STEP_BOSS_WHISPY_STATESHOTAIRBALLTORNADO_H

#include "scn/step/boss/whispy/StateShotAirBallBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateShotAirBallTornado : public StateShotAirBallBase {
public:
    StateShotAirBallTornado(Boss* boss, u32 count, u32 intervalFirst, u32 interval);
    virtual void reqAirBall();

private:
    f32 mSpeedAdd;
};

}
}
}
}

#endif
