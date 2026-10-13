#ifndef SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALLSTART_H
#define SCN_STEP_HERO_HIGHJUMP_STATEROCKETFALLSTART_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateRocketFallStart : public StateBase {
public:
    static bool tryToChangeState(Hero* hero);
    static bool tryToChangeStateFast(Hero* hero);

    StateRocketFallStart(Hero* hero, bool isFast);
    virtual ~StateRocketFallStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsFast;
};

}
}
}
}

#endif
