#ifndef SCN_STEP_BOSS_BONKERS_STATERAINBOMBSTART_H
#define SCN_STEP_BOSS_BONKERS_STATERAINBOMBSTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/bonkers/StateRainBomb.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateRainBombStart : public StateBase {
public:
    StateRainBombStart(Boss* boss, StateRainBomb::Config config);
    virtual ~StateRainBombStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsJump;
    u32 mCount;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mEndPos;
    StateRainBomb::Config mConfig;
};

}
}
}
}

#endif
