#ifndef SCN_STEP_HERO_DAMAGE_STATEHOVER_H
#define SCN_STEP_HERO_DAMAGE_STATEHOVER_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateHover : public StateBase {
public:
    StateHover(Hero* hero);
    virtual ~StateHover();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
