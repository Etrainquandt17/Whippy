#ifndef SCN_STEP_ENEMY_SHOTZO_STATESHOT_H
#define SCN_STEP_ENEMY_SHOTZO_STATESHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace shotzo {

class StateShot : public StateBase {
public:
    StateShot(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void shot();
    
    u32 mFrame;
};

}
}
}
}

#endif
