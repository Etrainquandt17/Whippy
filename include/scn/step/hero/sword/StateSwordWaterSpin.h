#ifndef SCN_STEP_HERO_SWORD_STATESWORDWATERSPIN_H
#define SCN_STEP_HERO_SWORD_STATESWORDWATERSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordWaterSpin : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSwordWaterSpin(Hero* hero);
    virtual ~StateSwordWaterSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsBubble;
    u32 mFrame;
};

}
}
}
}

#endif
