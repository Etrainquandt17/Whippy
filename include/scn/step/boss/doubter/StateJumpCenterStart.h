#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUMPCENTERSTART_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUMPCENTERSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJumpCenterStart : public StateBase {
public:
    StateJumpCenterStart(Boss* boss, f32 speed, u32 kind);
    virtual ~StateJumpCenterStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeed;
    u32 mKind;
};

}
}
}
}

#endif
