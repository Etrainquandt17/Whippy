#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEWAITLOW_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEWAITLOW_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateWaitLow : public IState {
public:
    StateWaitLow(Boss* boss);
    virtual ~StateWaitLow();
};

}

}}}  // namespace scn::step::boss

#endif
