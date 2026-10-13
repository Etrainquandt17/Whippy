#ifndef SCN_STEP_BOSS_WHISPY_STATEDAMAGEL_H
#define SCN_STEP_BOSS_WHISPY_STATEDAMAGEL_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateDamageL : public StateBase {
public:
    StateDamageL(Boss* boss);
    virtual ~StateDamageL();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
