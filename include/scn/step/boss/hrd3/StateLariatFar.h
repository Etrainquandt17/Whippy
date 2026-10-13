#ifndef SCN_STEP_BOSS_HRD3_STATELARIATFAR_H
#define SCN_STEP_BOSS_HRD3_STATELARIATFAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateLariatFar : public StateBase {
public:
    StateLariatFar(Boss* boss, u32 frame);
    virtual ~StateLariatFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    // TODO: name the phases.
    enum Phase {
        PHASE_0,
        PHASE_1,
        PHASE_2
    };

    void updateRotate();

    u32 mCount;
    u32 mFrame;
    f32 mRot;
    f32 mRotSpeed;
    Phase mPhase;
};

}
}
}
}

#endif
