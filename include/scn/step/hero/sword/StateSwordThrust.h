#ifndef SCN_STEP_HERO_SWORD_STATESWORDTHRUST_H
#define SCN_STEP_HERO_SWORD_STATESWORDTHRUST_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordThrust : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordThrust(Hero* hero);
    virtual ~StateSwordThrust();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsDash;
};

}
}
}
}

#endif
