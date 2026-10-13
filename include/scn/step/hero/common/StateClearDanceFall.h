#ifndef SCN_STEP_HERO_COMMON_STATECLEARDANCEFALL_H
#define SCN_STEP_HERO_COMMON_STATECLEARDANCEFALL_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateClearDanceFall : public StateBase {
public:
    StateClearDanceFall(Hero* hero);
    virtual ~StateClearDanceFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mZoom;
};

}
}
}
}

#endif
