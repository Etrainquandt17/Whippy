#ifndef SCN_STEP_BOSS_METALGENERAL_STATEMISSILE_H
#define SCN_STEP_BOSS_METALGENERAL_STATEMISSILE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StateMissile : public StateBase {
public:
    StateMissile(Boss* boss, u32 index);
    virtual ~StateMissile();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
