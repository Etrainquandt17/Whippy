#ifndef SCN_STEP_ENEMY_DAMAGE_STATEDEADEXTREME_H
#define SCN_STEP_ENEMY_DAMAGE_STATEDEADEXTREME_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateDeadExtreme : public StateBase {
public:
    StateDeadExtreme(Enemy* enemy, u32 reflectMax);
    virtual ~StateDeadExtreme();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    u32 mReflectCount;
    u32 _10;
    u32 mReflectMax;
    u32 mFrame;
};

}
}
}
}

#endif
