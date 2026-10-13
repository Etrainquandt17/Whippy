#ifndef SCN_STEP_BOSS_LANDIA_STATEAPPEAR_H
#define SCN_STEP_BOSS_LANDIA_STATEAPPEAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss, u32 zoomId);
    virtual ~StateAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void changePhaseZoomFall();
    void changePhaseZoomHowl();
    void changePhaseGlide();
    void changePhaseComeIn();
    void changePhaseHowl();
    void procAnimPhaseHowl();
    void startGame();
    void startBgm();
    void fogSetting(f32 rate);

    bool _8;
    bool _9;
    bool _A;
    u32 mPhase;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    u32 _2C;
    f32 _30;
    u32 mZoomId;
};

}
}
}
}

#endif
