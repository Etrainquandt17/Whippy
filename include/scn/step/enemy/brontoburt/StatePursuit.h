#ifndef SCN_STEP_ENEMY_BRONTOBURT_STATEPURSUIT_H
#define SCN_STEP_ENEMY_BRONTOBURT_STATEPURSUIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace brontoburt {

class StatePursuit : public StateBase {
public:
    StatePursuit(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
