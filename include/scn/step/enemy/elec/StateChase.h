#ifndef SCN_STEP_ENEMY_ELEC_STATECHASE_H
#define SCN_STEP_ENEMY_ELEC_STATECHASE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace elec {

class StateChase : public StateBase {
public:
    StateChase(Enemy* enemy);
    virtual void procMove();

private:
    u32 mFrame;
    u32 mNearFrame;
};

}
}
}
}

#endif
