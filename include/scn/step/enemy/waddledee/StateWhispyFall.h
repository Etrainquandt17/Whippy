#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATEWHISPYFALL_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATEWHISPYFALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateWhispyFall : public StateBase {
public:
    StateWhispyFall(Enemy* enemy);
    virtual ~StateWhispyFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
};

}
}
}
}

#endif
