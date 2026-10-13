#ifndef SCN_STEP_HERO_COMMON_STATESHOTAIRBALL_H
#define SCN_STEP_HERO_COMMON_STATESHOTAIRBALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateShotAirBall : public StateBase {
public:
    StateShotAirBall(Hero* hero);
    virtual ~StateShotAirBall();
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
