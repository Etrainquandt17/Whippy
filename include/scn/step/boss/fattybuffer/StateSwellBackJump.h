#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBACKJUMP_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBACKJUMP_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellBackJump : public StateBase {
public:
    StateSwellBackJump(Boss* boss, f32 speedH, f32 speedV);
    virtual ~StateSwellBackJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
