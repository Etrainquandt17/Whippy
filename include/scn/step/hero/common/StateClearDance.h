#ifndef SCN_STEP_HERO_COMMON_STATECLEARDANCE_H
#define SCN_STEP_HERO_COMMON_STATECLEARDANCE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateClearDance : public StateBase {
public:
    StateClearDance(Hero* hero);
    virtual ~StateClearDance();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsAnimEnd;
    u32 mFrame;
};

}
}
}
}

#endif
