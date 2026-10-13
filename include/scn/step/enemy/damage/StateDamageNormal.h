#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDAMAGENORMAL_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDAMAGENORMAL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDamageNormal : public StateBase {
public:
    StateDamageNormal(Enemy* enemy);
    virtual ~StateDamageNormal();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mEndFrame;
    bool mIsDeadNoItem;
};

}
}
}
}

#endif
