#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTALACTITELANDING_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTALACTITELANDING_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/fattybuffer/StalactiteJumpKind.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStalactiteLanding : public StateBase {
public:
    StateStalactiteLanding(Boss* boss, StalactiteJumpKind kind);
    virtual ~StateStalactiteLanding();
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
