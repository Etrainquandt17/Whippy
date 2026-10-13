#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEGLIDESTART_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEGLIDESTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleGlideStart : public StateBase {
public:
    StateTackleGlideStart(Boss* boss);
    virtual ~StateTackleGlideStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
