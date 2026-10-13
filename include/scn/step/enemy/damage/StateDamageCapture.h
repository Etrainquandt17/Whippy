#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDAMAGECAPTURE_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDAMAGECAPTURE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDamageCapture : public StateBase {
public:
    StateDamageCapture(Enemy* enemy);
    virtual ~StateDamageCapture();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mRot;
    bool mIsLanded;
    u32 mWait;
};

}
}
}
}

#endif
