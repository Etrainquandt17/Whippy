#ifndef SCN_STEP_ENEMY_FATTYBUFFERSTALACTITE_STATEFALL_H
#define SCN_STEP_ENEMY_FATTYBUFFERSTALACTITE_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace fattybufferstalactite {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy, f32 rot);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
};

}
}
}
}

#endif
