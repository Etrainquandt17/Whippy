#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATESTORMSTART_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATESTORMSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateStormStart : public IState {
public:
    StateStormStart(Boss* boss);
    virtual ~StateStormStart();
};

}}}}  // namespace scn::step::boss::mahoroabattle1

#endif
