#ifndef SCN_STEP_ENEMY_BOUNCY_STATELANDING_H
#define SCN_STEP_ENEMY_BOUNCY_STATELANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bouncy {

class StateLanding : public StateBase {
public:
    StateLanding(Enemy* enemy);
    virtual void procAnim();
};

}
}
}
}

#endif
