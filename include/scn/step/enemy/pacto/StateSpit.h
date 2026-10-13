#ifndef SCN_STEP_ENEMY_PACTO_STATESPIT_H
#define SCN_STEP_ENEMY_PACTO_STATESPIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pacto {

class StateSpit : public StateBase {
public:
    StateSpit(Enemy* enemy);
    virtual void procAnim();

private:
    u32 mFrame;
    bool mIsAnimEnd;
};

}
}
}
}

#endif
