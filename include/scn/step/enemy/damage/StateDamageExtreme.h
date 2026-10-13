#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDAMAGEEXTREME_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDAMAGEEXTREME_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDamageExtreme : public StateBase {
public:
    StateDamageExtreme(Enemy* enemy);
    virtual ~StateDamageExtreme();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    bool mIsReflected;
    u32 mFrame;
};

}
}
}
}

#endif
