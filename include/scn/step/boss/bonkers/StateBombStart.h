#ifndef SCN_STEP_BOSS_BONKERS_STATEBOMBSTART_H
#define SCN_STEP_BOSS_BONKERS_STATEBOMBSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateBombStart : public StateBase {
public:
    StateBombStart(Boss* boss);
    virtual ~StateBombStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
