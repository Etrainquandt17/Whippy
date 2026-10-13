#ifndef SCN_STEP_BOSS_LOWPER_STATEFIRST_H
#define SCN_STEP_BOSS_LOWPER_STATEFIRST_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFirst : public StateBase {
public:
    StateFirst(Boss* boss);
    virtual ~StateFirst();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
