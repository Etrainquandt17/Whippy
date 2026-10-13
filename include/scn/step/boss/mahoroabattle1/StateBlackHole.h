#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEBLACKHOLE_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEBLACKHOLE_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateBlackHole : public IState {
public:
    StateBlackHole(Boss* boss);
    virtual ~StateBlackHole();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
