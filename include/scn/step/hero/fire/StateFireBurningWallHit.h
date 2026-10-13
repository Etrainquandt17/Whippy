#ifndef SCN_STEP_HERO_FIRE_STATEFIREBURNINGWALLHIT_H
#define SCN_STEP_HERO_FIRE_STATEFIREBURNINGWALLHIT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

class StateFireBurningWallHit : public StateBase {
public:
    StateFireBurningWallHit(Hero* hero);
    virtual ~StateFireBurningWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
