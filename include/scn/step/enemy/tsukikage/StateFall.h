#ifndef SCN_STEP_ENEMY_TSUKIKAGE_STATEFALL_H
#define SCN_STEP_ENEMY_TSUKIKAGE_STATEFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tsukikage {

class StateFall : public StateBase {
public:
    StateFall(Enemy* enemy);
    virtual ~StateFall();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
