#ifndef SCN_STEP_BOSS_DOUBTER_STATEDEAD_H
#define SCN_STEP_BOSS_DOUBTER_STATEDEAD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

// TODO: members and the overrides.
class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
};

}
}
}
}

#endif
