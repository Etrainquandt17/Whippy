#ifndef SCN_STEP_HERO_COMMON_STATEPLANCHERLANDING_H
#define SCN_STEP_HERO_COMMON_STATEPLANCHERLANDING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StatePlancherLanding : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StatePlancherLanding(Hero* hero);
    virtual ~StatePlancherLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeedH;
    bool mIsAirContinue;
};

}
}
}
}

#endif
