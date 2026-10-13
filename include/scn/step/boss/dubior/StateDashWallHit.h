#ifndef SCN_STEP_BOSS_DUBIOR_STATEDASHWALLHIT_H
#define SCN_STEP_BOSS_DUBIOR_STATEDASHWALLHIT_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class StateDashWallHit : public StateBase {
public:
    StateDashWallHit(Boss* boss);
    virtual ~StateDashWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
