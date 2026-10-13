#ifndef SCN_STEP_BOSS_DOUBTER_STATEBOUND_H
#define SCN_STEP_BOSS_DOUBTER_STATEBOUND_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateBound : public StateBase {
public:
    StateBound(Boss* boss, const hel::math::Vector2& speed, u32 count);
    virtual ~StateBound();
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
