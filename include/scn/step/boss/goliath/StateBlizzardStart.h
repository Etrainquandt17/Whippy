#ifndef SCN_STEP_BOSS_GOLIATH_STATEBLIZZARDSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEBLIZZARDSTART_H

#include "scn/step/boss/goliath/BlizzardDesc.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace goliath {

// TODO: members.
class StateBlizzardStart : public IState {
public:
    StateBlizzardStart(Boss* boss, u32 _1, const BlizzardDesc& desc);
    virtual ~StateBlizzardStart();
};

}
}
}
}

#endif
