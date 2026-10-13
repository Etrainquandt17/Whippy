#ifndef SCN_STEP_BOSS_WHISPY_STATEDEAD_H
#define SCN_STEP_BOSS_WHISPY_STATEDEAD_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void stagingBossDead();

    u32 mCount;
    bool mIsStaged;
    hel::math::Vector3 mStartPos;
};

}
}
}
}

#endif
