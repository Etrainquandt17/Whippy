#ifndef SCN_STEP_BOSS_DOUBTER_STATEDAMAGEL_H
#define SCN_STEP_BOSS_DOUBTER_STATEDAMAGEL_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

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
