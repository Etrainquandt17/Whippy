#ifndef SCN_STEP_HERO_SWORD_STATESWORDUNDERTHRUSTSTART_H
#define SCN_STEP_HERO_SWORD_STATESWORDUNDERTHRUSTSTART_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordUnderThrustStart : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordUnderThrustStart(Hero* hero);
    virtual ~StateSwordUnderThrustStart();
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
