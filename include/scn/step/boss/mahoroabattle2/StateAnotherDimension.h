#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_STATEANOTHERDIMENSION_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_STATEANOTHERDIMENSION_H

#include "scn/step/boss/IState.h"
#include "scn/step/boss/mahoroabattle2/AnotherDimensionType.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace mahoroabattle2 {

// TODO: members.
class StateAnotherDimension : public IState {
public:
    StateAnotherDimension(Boss* boss, AnotherDimensionType type);
    virtual ~StateAnotherDimension();
};

}

}
}
}

#endif
