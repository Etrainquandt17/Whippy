#ifndef SCN_STEP_ENEMY_WALF_STATEMOVEONGROUND_H
#define SCN_STEP_ENEMY_WALF_STATEMOVEONGROUND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace walf {

class StateMoveOnGround : public StateBase {
public:
    StateMoveOnGround(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
