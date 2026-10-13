#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATESHOTBULLETFAR_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATESHOTBULLETFAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateShotBulletFar : public IState {
public:
    StateShotBulletFar(Boss* boss, const hel::math::Vector3& pos, bool _2);
    virtual ~StateShotBulletFar();
};

}

}
}
}

#endif
