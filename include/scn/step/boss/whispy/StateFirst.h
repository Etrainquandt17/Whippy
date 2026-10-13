#ifndef SCN_STEP_BOSS_WHISPY_STATEFIRST_H
#define SCN_STEP_BOSS_WHISPY_STATEFIRST_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateFirst : public StateBase {
public:
    StateFirst(Boss* boss);
    virtual ~StateFirst();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mStep;
    u32 mCount;
    f32 mSpeed;
};

}
}
}
}

#endif
