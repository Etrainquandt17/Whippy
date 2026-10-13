#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTICKROOFJUMP_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTICKROOFJUMP_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStickRoofJump : public StateBase {
public:
    StateStickRoofJump(Boss* boss);
    virtual ~StateStickRoofJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
