#ifndef SCN_STEP_HERO_FIRE_STATEFIREBURNINGEND_H
#define SCN_STEP_HERO_FIRE_STATEFIREBURNINGEND_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

class StateFireBurningEnd : public StateBase {
public:
    StateFireBurningEnd(Hero* hero);
    virtual ~StateFireBurningEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
