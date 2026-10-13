#ifndef SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPFALL_H
#define SCN_STEP_BOSS_DOUBTER_STATEETHERJUMPFALL_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateEtherJumpFall : public StateBase {
public:
    StateEtherJumpFall(Boss* boss);
    virtual ~StateEtherJumpFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
