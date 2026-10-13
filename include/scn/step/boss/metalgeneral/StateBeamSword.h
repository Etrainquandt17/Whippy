#ifndef SCN_STEP_BOSS_METALGENERAL_STATEBEAMSWORD_H
#define SCN_STEP_BOSS_METALGENERAL_STATEBEAMSWORD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateBeamSword : public StateBase {
public:
    StateBeamSword(Boss* boss, u32 scriptKind);
    virtual ~StateBeamSword();
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
