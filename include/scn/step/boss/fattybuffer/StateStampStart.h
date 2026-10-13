#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPSTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStampStart : public StateBase {
public:
    StateStampStart(Boss* boss, bool flag);
    virtual ~StateStampStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mFlag;
};

}
}
}
}

#endif
