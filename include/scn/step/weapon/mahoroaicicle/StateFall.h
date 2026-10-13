#ifndef SCN_STEP_WEAPON_MAHOROAICICLE_STATEFALL_H
#define SCN_STEP_WEAPON_MAHOROAICICLE_STATEFALL_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicicle {

class StateFall : public StateBase {
public:
    StateFall(Weapon* weapon, f32 rot);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeed;
    f32 mAccel;
    f32 mRot;
};

}
}
}
}

#endif
