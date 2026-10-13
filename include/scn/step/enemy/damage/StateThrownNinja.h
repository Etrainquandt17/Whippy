#ifndef SCN_STEP_ENEMY_DAMAGE_STATETHROWNNINJA_H
#define SCN_STEP_ENEMY_DAMAGE_STATETHROWNNINJA_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateThrownNinja : public StateBase {
public:
    StateThrownNinja(Enemy* enemy, u64 ownerUid, f32 speedRate);
    virtual ~StateThrownNinja();
    virtual void procAnim();
    virtual void procMove();

private:
    u32 mFrame;
};

}
}
}
}

#endif
