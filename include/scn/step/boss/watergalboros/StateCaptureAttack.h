#ifndef SCN_STEP_BOSS_WATERGALBOROS_STATECAPTUREATTACK_H
#define SCN_STEP_BOSS_WATERGALBOROS_STATECAPTUREATTACK_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class StateCaptureAttack : public StateBase {
public:
    StateCaptureAttack(Boss* boss);
    virtual ~StateCaptureAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procObjCollReact();

private:
    u32 mCount;
    bool mIsCapture;
    bool mIsSearch;
};

}
}
}
}

#endif
