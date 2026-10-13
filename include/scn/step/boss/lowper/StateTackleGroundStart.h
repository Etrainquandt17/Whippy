#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEGROUNDSTART_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEGROUNDSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleGroundStart : public StateBase {
public:
    StateTackleGroundStart(Boss* boss);
    virtual ~StateTackleGroundStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
