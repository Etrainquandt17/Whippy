#ifndef SCN_STEP_HERO_COMMON_STATEHOVERLANDING_H
#define SCN_STEP_HERO_COMMON_STATEHOVERLANDING_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateHoverLanding : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateHoverLanding(Hero* hero);
    virtual ~StateHoverLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
