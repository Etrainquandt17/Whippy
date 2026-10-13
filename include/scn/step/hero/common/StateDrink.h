#ifndef SCN_STEP_HERO_COMMON_STATEDRINK_H
#define SCN_STEP_HERO_COMMON_STATEDRINK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateDrink : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateDrink(Hero* hero);
    virtual ~StateDrink();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void checkMix();

    u32 _8;
    bool mIsSwallowed;
    bool mIsKeepAbility;
    bool mIsMix;
};

}
}
}
}

#endif
