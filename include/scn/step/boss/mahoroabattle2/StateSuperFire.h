#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERFIRE_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERFIRE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateSuperFire : public IState {
public:
    StateSuperFire(Boss* boss, f32 _1, f32 _2, f32 _3);
    virtual ~StateSuperFire();
};

}

}
}
}

#endif
