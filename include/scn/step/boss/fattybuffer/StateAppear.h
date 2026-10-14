#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEAPPEAR_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateAppear : public StateBase {
public:
    enum Phase {
        PHASE_HIDING_END,
        PHASE_APPEAR_JUMP,
        PHASE_APPEAR,
    };

    StateAppear(Boss* boss);
    virtual ~StateAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void changePhase(Phase phase);
    void startGame();
    void startBgm();
    void setupCameraLock();

    Phase mPhase;
    u32 mFrame;
    bool mIsWaitDemo;
    bool mIsGameStarted;
    bool mIsBgmStarted;
    bool mIsFirstAppear;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
