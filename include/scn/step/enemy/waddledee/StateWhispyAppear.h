#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATEWHISPYAPPEAR_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATEWHISPYAPPEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateWhispyAppear : public StateBase {
public:
    StateWhispyAppear(Enemy* enemy);
    virtual ~StateWhispyAppear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mBaseY;
};

}
}
}
}

#endif
