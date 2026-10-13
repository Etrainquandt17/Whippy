#ifndef SCN_STEP_BOSS_METALGENERAL_STATEMOVEGROUND_H
#define SCN_STEP_BOSS_METALGENERAL_STATEMOVEGROUND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateMoveGround : public StateBase {
public:
    StateMoveGround(Boss* boss, u32 scriptKind);
    virtual ~StateMoveGround();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mScriptKind;
};

}
}
}
}

#endif
