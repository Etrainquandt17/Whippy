#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEATTACK_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/AttackDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateAttack : public StateBase {
public:
    StateAttack(Boss* boss, const AttackDesc& desc);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void generateStar();
    void generateMoonShot();
    u32 mFrame;
    u32 mCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
    bool mIsMove;
    bool mIsMoonShot;
};

}
}
}
}

#endif
