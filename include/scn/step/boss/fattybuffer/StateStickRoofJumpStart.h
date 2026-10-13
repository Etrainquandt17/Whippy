#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTICKROOFJUMPSTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTICKROOFJUMPSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStickRoofJumpStart : public StateBase {
public:
    StateStickRoofJumpStart(Boss* boss);
    virtual ~StateStickRoofJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
