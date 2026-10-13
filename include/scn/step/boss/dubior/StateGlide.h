#ifndef SCN_STEP_BOSS_DUBIOR_STATEGLIDE_H
#define SCN_STEP_BOSS_DUBIOR_STATEGLIDE_H

#include "scn/step/boss/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace dubior {

// TODO: members.
class StateGlide : public IState {
public:
    StateGlide(Boss* boss);
    virtual ~StateGlide();
};

}

}}}  // namespace scn::step::boss

#endif
