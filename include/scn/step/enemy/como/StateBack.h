#ifndef SCN_STEP_ENEMY_COMO_STATEBACK_H
#define SCN_STEP_ENEMY_COMO_STATEBACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class StateBack : public StateBase {
public:
    StateBack(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mFrame;
    f32 mStartLength;
};

}
}
}
}

#endif
