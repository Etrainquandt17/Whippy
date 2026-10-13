#ifndef SCN_STEP_BOSS_LANDIA_COLLISIONCTRL_H
#define SCN_STEP_BOSS_LANDIA_COLLISIONCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

}
class Boss;
namespace landia {

// TODO: members, the other functions, and the names of the enumerators.
class CollisionCtrl {
public:
    enum State {
        STATE_0,
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6,
        STATE_7,
        STATE_8,
    };

    CollisionCtrl(Boss& boss);
    void setState(State state);
};

}
}
}
}

#endif
