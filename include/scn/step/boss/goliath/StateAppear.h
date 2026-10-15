#ifndef SCN_STEP_BOSS_GOLIATH_STATEAPPEAR_H
#define SCN_STEP_BOSS_GOLIATH_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss);
    virtual ~StateAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void startGame();
    void startBgm();
    void setCameraLock();
    void updateRotate();

    bool mIsWaitDemoReady;
    bool mIsGameStarted;
    bool mIsBgmStarted;
    bool mIsCameraLocked;
    u32 mWaitFrame;
    u32 mFrame;
    f32 mRot;
    f32 mRotSpeed;
};

}}}}  // namespace scn::step::boss::goliath

#endif
