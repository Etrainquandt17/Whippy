#ifndef SCN_STEP_BOSS_ROAH_STATEOAR_H
#define SCN_STEP_BOSS_ROAH_STATEOAR_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateOar : public StateBase {
public:
    StateOar(Boss* boss);
    virtual ~StateOar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mBasePos;
    bool mIsMove;
    bool mIsOarLost;
    bool mIsRequest;
};

}
}
}
}

#endif
