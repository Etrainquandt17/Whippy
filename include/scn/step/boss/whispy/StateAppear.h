#ifndef SCN_STEP_BOSS_WHISPY_STATEAPPEAR_H
#define SCN_STEP_BOSS_WHISPY_STATEAPPEAR_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

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

    bool mIsWaitDemoReady;
    bool mIsGameStarted;
    bool mIsBgmStarted;
};

}
}
}
}

#endif
