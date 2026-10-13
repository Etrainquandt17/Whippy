#ifndef SCN_STEP_ENEMY_DAMAGE_STATETHROWNFIGHTER_H
#define SCN_STEP_ENEMY_DAMAGE_STATETHROWNFIGHTER_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateThrownFighter : public StateBase {
public:
    StateThrownFighter(Enemy* enemy, u64 ownerUid);
    virtual ~StateThrownFighter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mRot;
    bool mIsReflected;
    u32 mWait;
};

}
}
}
}

#endif
