#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDAMAGEWINGTOSS_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDAMAGEWINGTOSS_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDamageWingToss : public StateBase {
public:
    StateDamageWingToss(Enemy* enemy);
    virtual ~StateDamageWingToss();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void recover();

private:
    bool mIsBound;
    u32 mFrame;
    u32 mCollFrame;
};

}
}
}
}

#endif
