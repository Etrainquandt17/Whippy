#ifndef SCN_STEP_BOSS_WATERGALBOROS_STATEQUIVERY_H
#define SCN_STEP_BOSS_WATERGALBOROS_STATEQUIVERY_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class StateQuivery : public StateBase {
public:
    struct Config {
        u32 _0;
        u32 _4;
    };

    StateQuivery(Boss* boss, Config config);
    virtual ~StateQuivery();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void reqQuivery();

private:
    f32 mRot;
    u32 mCount;
    Config mConfig;
    bool mIsStart;
};

}
}
}
}

#endif
