#ifndef SCN_STEP_BOSS_GUARD_H
#define SCN_STEP_BOSS_GUARD_H

#include "scn/step/boss/GuardType.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

// TODO: members.
class Guard {
public:
    Guard();

    void setType(GuardType type);
    u32 calcDamage(u32 damage, f32 rate);

private:
    GuardType mType;
};

}
}
}

#endif
