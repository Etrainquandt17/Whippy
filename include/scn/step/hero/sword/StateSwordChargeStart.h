#ifndef SCN_STEP_HERO_SWORD_STATESWORDCHARGESTART_H
#define SCN_STEP_HERO_SWORD_STATESWORDCHARGESTART_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordChargeStart : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordChargeStart(Hero* hero);
    virtual ~StateSwordChargeStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
