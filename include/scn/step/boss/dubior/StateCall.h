#ifndef SCN_STEP_BOSS_DUBIOR_STATECALL_H
#define SCN_STEP_BOSS_DUBIOR_STATECALL_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateCall : public StateBase {
public:
    StateCall(Boss* boss, u32 kind);
    virtual ~StateCall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqDubiorJr();

    u32 mKind;
};

}
}
}
}

#endif
