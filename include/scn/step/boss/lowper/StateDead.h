#ifndef SCN_STEP_BOSS_LOWPER_STATEDEAD_H
#define SCN_STEP_BOSS_LOWPER_STATEDEAD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateDead : public StateBase {
public:
    StateDead(Boss* boss);
    virtual ~StateDead();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mRotV;
};

}
}
}
}

#endif
