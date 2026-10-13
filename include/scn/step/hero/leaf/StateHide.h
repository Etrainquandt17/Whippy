#ifndef SCN_STEP_HERO_LEAF_STATEHIDE_H
#define SCN_STEP_HERO_LEAF_STATEHIDE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class StateHide : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateHide(Hero* hero);
    virtual ~StateHide();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
