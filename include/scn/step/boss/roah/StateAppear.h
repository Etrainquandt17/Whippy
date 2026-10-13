#ifndef SCN_STEP_BOSS_ROAH_STATEAPPEAR_H
#define SCN_STEP_BOSS_ROAH_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateAppear : public StateBase {
public:
    StateAppear(Boss* boss);
    virtual ~StateAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void startGame();

    u32 mCount;
    u32 mMoveFrame;
    bool mIsMove;
    bool mIsWaitDemo;
    bool mIsStarted;
    u32 mCameraCount;
    bool mIsCameraRot;
};

}}}}  // namespace scn::step::boss::roah

#endif
