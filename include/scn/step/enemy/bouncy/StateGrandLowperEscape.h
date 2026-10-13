#ifndef SCN_STEP_ENEMY_BOUNCY_STATEGRANDLOWPERESCAPE_H
#define SCN_STEP_ENEMY_BOUNCY_STATEGRANDLOWPERESCAPE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bouncy {

class StateGrandLowperEscape : public StateBase {
public:
    StateGrandLowperEscape(Enemy* enemy);
    virtual ~StateGrandLowperEscape();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
