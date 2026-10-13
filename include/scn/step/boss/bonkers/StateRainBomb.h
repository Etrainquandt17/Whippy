#ifndef SCN_STEP_BOSS_BONKERS_STATERAINBOMB_H
#define SCN_STEP_BOSS_BONKERS_STATERAINBOMB_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateRainBomb : public StateBase {
public:
    struct Config {
        bool _0;
    };

    StateRainBomb(Boss* boss, Config config);
    virtual ~StateRainBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBomb();

    u32 mStartCount;
    u32 mCount;
    u32 mEndCount;
    u32 mBombNum;
    u32 mBigBombIndex;
};

}
}
}
}

#include "scn/step/boss/bonkers/StateRainBombStart.h"

#endif
