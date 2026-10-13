#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUGGLINGATTACK2_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUGGLINGATTACK2_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJugglingAttack2 : public StateBase {
public:
    StateJugglingAttack2(Boss* boss);
    virtual ~StateJugglingAttack2();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 _8;
};

}
}
}
}

#endif
