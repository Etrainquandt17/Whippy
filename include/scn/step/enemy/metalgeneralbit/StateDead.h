#ifndef SCN_STEP_ENEMY_METALGENERALBIT_STATEDEAD_H
#define SCN_STEP_ENEMY_METALGENERALBIT_STATEDEAD_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace metalgeneralbit {

class StateDead : public StateBase {
public:
    StateDead(Enemy* enemy);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
