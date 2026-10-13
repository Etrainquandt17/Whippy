#ifndef SCN_STEP_BOSS_COMMON_STATEMOVEJOINT_H
#define SCN_STEP_BOSS_COMMON_STATEMOVEJOINT_H

#include "gobj/MoveParam.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

struct StateMoveJointDesc {
    StateMoveJointDesc(gobj::MoveParamDecel decel);

    gobj::MoveParamDecel _0;
};

class StateMoveJoint : public StateBase {
public:
    StateMoveJoint(Boss* boss, StateMoveJointDesc desc, u32 scriptKind);
    virtual ~StateMoveJoint();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateMoveJointDesc mDesc;
};

}
}
}
}

#endif
