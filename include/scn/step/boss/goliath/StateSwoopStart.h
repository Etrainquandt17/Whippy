#ifndef SCN_STEP_BOSS_GOLIATH_STATESWOOPSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATESWOOPSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateSwoopStart : public IState {
public:
    StateSwoopStart(Boss* boss, u32 _1, u32 _2);
    virtual ~StateSwoopStart();
};

}
}
}
}

#endif
