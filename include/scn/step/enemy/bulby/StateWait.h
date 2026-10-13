#ifndef SCN_STEP_ENEMY_BULBY_STATEWAIT_H
#define SCN_STEP_ENEMY_BULBY_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bulby {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procFixPos();

private:
    void smoke();
    void setHitFlag(bool flag);
    
    u32 mFrame;
};

}
}
}
}

#endif
