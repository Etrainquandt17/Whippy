#ifndef SCN_STEP_ENEMY_BRONTOBURT_STATEFLY_H
#define SCN_STEP_ENEMY_BRONTOBURT_STATEFLY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace brontoburt {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mStartX;
};

}
}
}
}

#endif
