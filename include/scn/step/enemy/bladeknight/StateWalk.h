#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_STATEWALK_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_STATEWALK_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bladeknight {

class StateWalk : public StateBase {
public:
    StateWalk(Enemy* enemy);
    virtual ~StateWalk();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
