#ifndef SCN_STEP_BOSS_HRD3PILOT_STATEMISSILE_H
#define SCN_STEP_BOSS_HRD3PILOT_STATEMISSILE_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/enemy/metalgeneralmissile/StateSpread.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

class StateMissile : public StateBase {
public:
    StateMissile(Boss* boss);
    virtual ~StateMissile();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void reqMissile(enemy::metalgeneralmissile::StateSpread::SpreadKind kind);
};

}
}
}
}

#endif
