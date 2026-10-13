#ifndef SCN_STEP_BOSS_ZANKIBBLE_STATECATCH_H
#define SCN_STEP_BOSS_ZANKIBBLE_STATECATCH_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

class StateCatch : public StateBase {
public:
    StateCatch(Boss* boss);
    virtual ~StateCatch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsCaught;
};

}
}
}
}

#endif
