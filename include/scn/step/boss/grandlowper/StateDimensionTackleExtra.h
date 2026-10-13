#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEDIMENSIONTACKLEEXTRA_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEDIMENSIONTACKLEEXTRA_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateDimensionTackleExtra : public IState {
public:
    StateDimensionTackleExtra(Boss* boss, u32 _1);
    virtual ~StateDimensionTackleExtra();
};

}

}
}
}

#endif
