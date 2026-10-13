#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEHOMINGSHOT_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEHOMINGSHOT_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateHomingShot : public IState {
public:
    StateHomingShot(Boss* boss, u32 _1);
    virtual ~StateHomingShot();
};

}

}}}  // namespace scn::step::boss

#endif
