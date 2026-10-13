#ifndef SCN_STEP_ENEMY_BARRACU_STATEPURSUIT_H
#define SCN_STEP_ENEMY_BARRACU_STATEPURSUIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace barracu {

class StatePursuit : public StateBase {
public:
    StatePursuit(Enemy* enemy);
    virtual ~StatePursuit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mTurnFrame;
    u32 mFrame;
};

}
}
}
}

#endif
