#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATETORNADOATTACK_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATETORNADOATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/hero/CaptureHeroAttacker.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateTornadoAttack : public StateBase {
public:
    StateTornadoAttack(Boss* boss);
    virtual ~StateTornadoAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    void changeStateLanding();
    f32 mFloorY;
    f32 mSign;
    hel::math::Vector3 mVelocity;
    hero::CaptureHeroAttacker mAttacker;
};

}
}
}
}

#endif
