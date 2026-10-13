#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEFREEZEATTACKSTART_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEFREEZEATTACKSTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateFreezeAttackStart : public IState {
public:
    StateFreezeAttackStart(Boss* boss, const hel::math::Vector3& pos, u32 _2);
    virtual ~StateFreezeAttackStart();
};

}

}
}
}

#endif
