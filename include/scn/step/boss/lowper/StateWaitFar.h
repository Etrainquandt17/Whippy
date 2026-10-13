#ifndef SCN_STEP_BOSS_LOWPER_STATEWAITFAR_H
#define SCN_STEP_BOSS_LOWPER_STATEWAITFAR_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateWaitFar : public StateBase {
public:
    StateWaitFar(Boss* boss);
    virtual ~StateWaitFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mPos;
    f32 _10;
    f32 _14;
};

}
}
}
}

#endif
