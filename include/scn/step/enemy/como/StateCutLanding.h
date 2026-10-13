#ifndef SCN_STEP_ENEMY_COMO_STATECUTLANDING_H
#define SCN_STEP_ENEMY_COMO_STATECUTLANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class StateCutLanding : public StateBase {
public:
    StateCutLanding(Enemy* enemy);
    virtual ~StateCutLanding();
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
