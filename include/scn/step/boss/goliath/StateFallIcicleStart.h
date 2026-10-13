#ifndef SCN_STEP_BOSS_GOLIATH_STATEFALLICICLESTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEFALLICICLESTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateFallIcicleStart : public IState {
public:
    StateFallIcicleStart(Boss* boss, u32 _1, u32 _2);
    virtual ~StateFallIcicleStart();
};

}
}
}
}

#endif
