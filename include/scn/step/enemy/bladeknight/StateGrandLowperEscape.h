#ifndef SCN_STEP_ENEMY_BLADEKNIGHT_STATEGRANDLOWPERESCAPE_H
#define SCN_STEP_ENEMY_BLADEKNIGHT_STATEGRANDLOWPERESCAPE_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

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
