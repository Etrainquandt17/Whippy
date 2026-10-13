#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATEMOVEFAR_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATEMOVEFAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateMoveFar : public IState {
public:
    StateMoveFar(Boss* boss, const hel::math::Vector3& pos, u32 _2);
    virtual ~StateMoveFar();
};

}
}
}
}

#endif
