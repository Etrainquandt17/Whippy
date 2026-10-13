#ifndef SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALLWALLHIT_H
#define SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALLWALLHIT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateRocketFallWallHit : public StateBase {
public:
    StateRocketFallWallHit(Hero* hero);
    virtual ~StateRocketFallWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}
}
}
}

#endif
