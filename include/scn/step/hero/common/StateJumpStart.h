#ifndef SCN_STEP_HERO_COMMON_STATEJUMPSTART_H
#define SCN_STEP_HERO_COMMON_STATEJUMPSTART_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateJumpStart : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateJumpStart(Hero* hero);
    virtual ~StateJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeedH;
    f32 mSpeedV;
};

}
}
}
}

#endif
