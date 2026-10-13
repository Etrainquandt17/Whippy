#ifndef SCN_STEP_BOSS_GRANDLOWPER_STATEDIMENSIONSEARCH_H
#define SCN_STEP_BOSS_GRANDLOWPER_STATEDIMENSIONSEARCH_H

#include "scn/step/boss/IState.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace grandlowper {

// TODO: members.
class StateDimensionSearch : public IState {
public:
    StateDimensionSearch(Boss* boss);
    virtual ~StateDimensionSearch();
};

}

}
}
}

#endif
