#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTALACTITESTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTALACTITESTART_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/fattybuffer/StalactiteJumpKind.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStalactiteStart : public StateBase {
public:
    StateStalactiteStart(Boss* boss, StalactiteJumpKind kind);
    virtual ~StateStalactiteStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StalactiteJumpKind mKind;
};

}
}
}
}

#endif
