#ifndef SCN_STEP_BOSS_ROAH_STATEDEAD_H
#define SCN_STEP_BOSS_ROAH_STATEDEAD_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void stagingBossDead();

    bool _8;
    bool mIsStaged;
    bool mIsFirst;
    hel::math::Vector3 mRot;
};

}
}
}
}

#endif
