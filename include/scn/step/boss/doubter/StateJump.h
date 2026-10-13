#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUMP_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUMP_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJump : public StateBase {
public:
    StateJump(Boss* boss, const hel::math::Vector2& speed, u32 count);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}
}
}
}

#endif
