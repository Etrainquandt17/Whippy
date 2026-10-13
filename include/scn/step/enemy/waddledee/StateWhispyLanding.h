#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATEWHISPYLANDING_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATEWHISPYLANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateWhispyLanding : public StateBase {
public:
    StateWhispyLanding(Enemy* enemy);
    virtual ~StateWhispyLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
