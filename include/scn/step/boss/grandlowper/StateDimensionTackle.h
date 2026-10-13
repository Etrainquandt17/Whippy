#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEDIMENSIONTACKLE_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEDIMENSIONTACKLE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateDimensionTackle : public IState {
public:
    StateDimensionTackle(Boss* boss);
    virtual ~StateDimensionTackle();
};

}

}
}
}

#endif
