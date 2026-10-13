#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_STATETACKLESTART_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_STATETACKLESTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle1 {

// TODO: members.
class StateTackleStart : public IState {
public:
    StateTackleStart(Boss* boss, const hel::math::Vector3& pos, u32 _2, f32 _3);
    virtual ~StateTackleStart();
};

}
}
}
}

#endif
