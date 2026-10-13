#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERBEAMSTART_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATESUPERBEAMSTART_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateSuperBeamStart : public IState {
public:
    StateSuperBeamStart(Boss* boss, u32 _1, u32 _2, u32 _3, u32 _4);
    virtual ~StateSuperBeamStart();
};

}

}}}  // namespace scn::step::boss

#endif
