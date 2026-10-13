#ifndef SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPRISE_H
#define SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPRISE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateEtherJumpRise : public StateBase {
public:
    StateEtherJumpRise(Boss* boss, u32 frame);
    virtual ~StateEtherJumpRise();
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
