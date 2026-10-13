#ifndef SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTTACKLE_H
#define SCN_STEP_BOSS_METALGENERAL_STATEPATRIOTTACKLE_H

#include "hel/math/Direction3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

// TODO: members.
class StatePatriotTackle : public StateBase {
public:
    StatePatriotTackle(Boss* boss, hel::math::Direction3 dir);
    virtual ~StatePatriotTackle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
